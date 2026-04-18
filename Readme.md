PROJET CMI - COMPTAGE DE PERSONNES
---------------------------------

1. DESCRIPTION DU PROJET
Ce projet est un système de comptage en temps réel. Des capteurs Arduino détectent les entrées et sorties d'une salle. Ces données sont envoyées à un serveur sécurisé en C++ qui met à jour une base de données SQLite. Une interface web en Python (Flask) permet de visualiser les résultats.

Travail de Groupe à 3, réalisé par : Nassim Benchenni, Nicolas Di Grande, Fouad Sbaghi.

2. STRUCTURE DES FICHIERS
- server.py : Serveur web principal (Flask) gérant l'affichage et l'API.
- update.py : Scripts Python pour modifier la base de données salle.db.
- app.cpp : Serveur de réception sécurisé (SSL/TLS) écrit en C++.
- Makefile : Fichier de compilation pour le programme C++.
- salle.db : Base de données SQLite stockant le nombre de personnes.
- index.html : Interface utilisateur web.
- static/ : Contient les styles CSS et les scripts JS pour le web.
- Arduino/arduino.ino : Code pour la carte Arduino et les capteurs.
- server_certificate/ : Certificats SSL requis pour la connexion sécurisée.

3. INSTALLATION (SUR LINUX / WSL)
- Installer Flask (Python) : sudo apt install python3-flask
- Installer les dépendances C++ : sudo apt install g++ libssl-dev libsqlite3-dev

4. UTILISATION ÉTAPE PAR ÉTAPE

Étape 1 : Branchements Matériels (Arduino)
1. Prenez vos deux capteurs de passage (ex: infrarouge ou laser).
2. Branchez le fil de signal du Capteur 1 sur la broche numérique 2 (Pin 2) de l'Arduino.
3. Branchez le fil de signal du Capteur 2 sur la broche numérique 3 (Pin 3) de l'Arduino.
4. (N'oubliez pas de relier le 5V et le GND des capteurs à l'Arduino).
5. Branchez l'écran LCD RGB sur le port I2C (broches SDA et SCL).
6. Connectez la carte Arduino à votre ordinateur via un câble USB.
7. Ouvrez Arduino/arduino.ino dans l'IDE Arduino et téléversez le code.

Étape 2 : Lancer le Dashboard Web
Dans un terminal, tapez : python3 server.py
L'interface sera accessible sur http://localhost:5000

Étape 3 : Lancer le Serveur de Réception C++
Dans un second terminal :
1. Tapez 'make' pour compiler le projet (si ce n'est pas déjà fait).
2. Tapez './prog' pour lancer le serveur sécurisé. Il se mettra en atte
5. NOTES TECHNIQUES & RÉSEAU
- Pour que l'Arduino puisse envoyer ses données, il devra cibler l'adresse IP locale (IPv4) de l'ordinateur hébergeant le serveur C++ sur le port 8080.
- Les communications entre le matériel et le serveur sont sécurisées par TLS.