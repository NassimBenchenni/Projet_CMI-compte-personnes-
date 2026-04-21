PROJET CMI - COMPTAGE DE PERSONNES
---------------------------------

1. DESCRIPTION DU PROJET
Ce projet est un système de comptage en temps réel. Des capteurs Arduino détectent les entrées et sorties d'une salle. Ces données sont envoyées à un serveur sécurisé en C++ qui met à jour une base de données SQLite. Une interface web en Python (Flask) permet de visualiser les résultats.

Travail de Groupe à 3, réalisé par : Nassim Benchenni, Nicolas Di Grande, Fouad Sbaghi.

2. STRUCTURE DES FICHIERS
- server.py : Serveur web principal (Flask) gérant l'affichage et l'API.
- update.py : Fonctions Python pour modifier la base de données salle.db.
- app.cpp : Serveur de réception sécurisé (SSL/TLS) écrit en C++.
- Makefile : Fichier de compilation pour le programme C++.
- salle.sql : Schéma de création de la base de données (si création manuelle).
- Arduino/arduino.ino : Code pour la carte Arduino (Pins 2 et 3).

3. INSTALLATION (LINUX / WSL)
- Python et Flask : sudo apt install python3-flask
- Dépendances C++ : sudo apt install g++ libssl-dev libsqlite3-dev
- Génération des certificats de test : Génération des certificats de test

4. UTILISATION
Etape 1 : Configuration Matérielle
1. Reliez le Capteur 1 à la Pin 2 et le Capteur 2 à la Pin 3 de l'Arduino.
2. Branchez l'écran LCD sur les ports I2C.
3. Televersez le code via l'IDE Arduino.

Etape 2 : Lancement du Dashboard Web
Dans un terminal : python3 server.py
La base de données 'salle.db' est créée automatiquement au premier lancement.
L'interface est accessible sur http://localhost:5000.

Etape 3 : Lancement du Serveur C++
Dans un second terminal :
1. Tapez 'make' pour compiler.
2. Tapez './prog' pour lancer la réception des données.

5. SECURITE ET RESEAU
- Le dossier 'server_certificate/' est exclu du depot public pour des raisons de securite (contient les cles privees). 
- Pour une utilisation en production ou en public, vous devez generer vos propres certificats SSL et les placer dans ce dossier.
- Le serveur C++ ecoute par defaut sur 0.0.0.0:8080.
