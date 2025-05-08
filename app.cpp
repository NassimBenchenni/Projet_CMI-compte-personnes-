#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <cstring>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 8080
#define SERVER_IP "192.168.110.1"


bool updatePeopleCount(const std::string& db_name, int room_id, int new_count) {
    sqlite3* db;
    char* errorMessage = nullptr;

    // Ouvrir la base de données
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Erreur ouverture base de données: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Requête SQL de mise à jour
    std::string sql = "UPDATE salle SET nombre_personnes = " + std::to_string(new_count) +
                      " WHERE id = " + std::to_string(room_id) + ";";

    // Exécuter la requête
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erreur mise à jour: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        sqlite3_close(db);
        return false;
    }

    std::cout << "Mise à jour réussie: Salle " << room_id << " -> " << new_count << " personnes" << std::endl;

    // Fermer la base de données
    sqlite3_close(db);
    return true;
}


void handleError(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}


int main() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    // Créer le contexte SSL
    const SSL_METHOD* method = TLS_server_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    if (!ctx) {
        handleError("Impossible de créer le contexte SSL");
    }

    // Charger le certificat et la clé privée
    if (SSL_CTX_use_certificate_file(ctx, "server_certificate/server.crt", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, "server_certificate/server.key", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    // Vérifier que la clé privée correspond au certificat
    if (!SSL_CTX_check_private_key(ctx)) {
        handleError("La clé privée ne correspond pas au certificat public");
    }

    // Configurer le socket serveur
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        handleError("Échec de la création du socket");
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(SERVER_IP);
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        handleError("Échec du bind");
    }
    if (listen(server_fd, 1) < 0) {
        handleError("Échec du listen");
    }

    std::cout << "Serveur sécurisé en attente de connexions sur " << SERVER_IP << ":" << PORT << "..." << std::endl;

    // Données de réception pour la modification de la base SQLite
    std::string db_name = "salle.db"; // Nom de la base SQLite
    int room_id = 1; // ID de la salle à modifier
    int new_count;

    while (true) {
        int addrlen = sizeof(address);
        int client_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            handleError("Échec de l'acceptation du client");
        }

        std::cout << "Nouvelle connexion reçue." << std::endl;

        // Créer une connexion SSL pour le client
        SSL* ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client_fd);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
            SSL_free(ssl);
            close(client_fd);
            continue;  // Revenir en attente d'un nouveau client
        }

        std::cout << "Connexion sécurisée établie avec le client." << std::endl;

        std::vector<int> receivedData;
        int buffer[1024];
        int bytesRead;

        while (true) {
            bytesRead = SSL_read(ssl, buffer, sizeof(buffer));
            if (bytesRead <= 0) {
                int sslError = SSL_get_error(ssl, bytesRead);
                if (sslError == SSL_ERROR_ZERO_RETURN) {
                    std::cout << "Le client a fermé la connexion proprement." << std::endl;
                } else {
                    std::cerr << "Erreur SSL lors de la lecture : " << sslError << std::endl;
                }
                break; // Sortir de la boucle de lecture pour accepter un nouveau client
            }

            std::cout << "Reçu " << bytesRead << " octets." << std::endl;

            if (bytesRead == 3 && strncmp((char*)buffer, "FIN", 3) == 0) {
                std::cout << "Fin de la transmission demandée par le client." << std::endl;
                break;
            }

            int numElements = bytesRead / sizeof(int);
            for (int i = 0; i < numElements; ++i) {
                receivedData.push_back(buffer[i]);
            }

            // Envoyer une confirmation après réception des données
            const char* confirmation = "OK";
            if (SSL_write(ssl, confirmation, strlen(confirmation)) <= 0) {
                std::cerr << "Erreur SSL lors de l'envoi de la confirmation." << std::endl;
            }
        }

        if (!receivedData.empty()) {
            std::cout << "Données reçues : ";
            for (int num : receivedData) {
                std::cout << num << " ";
            }
            std::cout << std::endl;

            // Mettre à jour la base SQLite avec la dernière valeur reçue
            new_count = receivedData.back();
            if (updatePeopleCount(db_name, room_id, new_count)) {
                std::cout << "Mise à jour effectuée avec succès !" << std::endl;
            } else {
                std::cout << "Échec de la mise à jour." << std::endl;
            }
        }

        // Nettoyage de la connexion
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client_fd);
        std::cout << "Connexion fermée, attente d'un nouveau client..." << std::endl;
    }

    // Nettoyage global du serveur (ne sera jamais atteint en usage normal)
    close(server_fd);
    SSL_CTX_free(ctx);
    EVP_cleanup();

    return 0;
}
