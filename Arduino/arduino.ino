
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// Variable de comptage (accessible en ISR et dans loop)
volatile int compteur = 0;

// Variables pour la gestion de la séquence de détection
// first_sensor vaut 0 (aucun), 1 (capteur 1 déclenché en premier) ou 2 (capteur 2 déclenché en premier)
volatile int first_sensor = 0;         
volatile unsigned long first_trigger_time = 0; // Temps du premier déclenchement
volatile bool waiting_for_second = false;       // On attend le second capteur

const unsigned long passageTimeout = 3000; // Délai maximum entre les deux capteurs (en ms)

//
// ISR pour le capteur 1 (broche 2, INT0)
//
void sensor1_ISR() {
  unsigned long now = millis();
  
  // Si aucun capteur n'a été déclenché, on enregistre le capteur 1 comme premier
  if (first_sensor == 0) {
    first_sensor = 1;
    first_trigger_time = now;
    waiting_for_second = true;
  }
  // Sinon, si c'est le second déclenchement et qu'il complète une séquence sortie
  else if (waiting_for_second && first_sensor == 2) {
    // capteur 2 était déclenché en premier, maintenant capteur 1 valide une sortie
    if (now - first_trigger_time < passageTimeout) {
      compteur--; // sortie validée
    }
    // Réinitialiser l'état
    waiting_for_second = false;
    first_sensor = 0;
  }
}

//
// ISR pour le capteur 2 (broche 3, INT1)
//
void sensor2_ISR() {
  unsigned long now = millis();
  
  // Si aucun capteur n'a été déclenché, on enregistre le capteur 2 comme premier
  if (first_sensor == 0) {
    first_sensor = 2;
    first_trigger_time = now;
    waiting_for_second = true;
  }
  // Sinon, si c'est le second déclenchement et qu'il complète une séquence entrée
  else if (waiting_for_second && first_sensor == 1) {
    // capteur 1 était déclenché en premier, maintenant capteur 2 valide une entrée
    if (now - first_trigger_time < passageTimeout) {
      compteur++; // entrée validée
    }
    // Réinitialiser l'état
    waiting_for_second = false;
    first_sensor = 0;
  }
}

//
// Configuration initiale
//
void setup() {
  Serial.begin(9600);

  // Configure les capteurs sur les broches 2 et 3 en mode INPUT_PULLUP
  pinMode(2, INPUT_PULLUP); // Capteur 1 (INT0)
  pinMode(3, INPUT_PULLUP); // Capteur 2 (INT1)

  // Attache les interruptions sur le front descendant (passage de HIGH à LOW)
  attachInterrupt(digitalPinToInterrupt(2), sensor1_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), sensor2_ISR, FALLING);

  // Initialisation de l'écran LCD
  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);
  lcd.setCursor(0, 0);
  lcd.print("Compteur: ");
  lcd.print(compteur);
}

//
// Boucle principale
//
void loop() {
  unsigned long now = millis();

  // Si on attend le second capteur et que le délai est dépassé, on réinitialise l'état
  if (waiting_for_second && (now - first_trigger_time >= passageTimeout)) {
    waiting_for_second = false;
    first_sensor = 0;
  }

  if (compteur<0){
    compteur=0;
  }

  // Mise à jour de l'affichage LCD
  lcd.setCursor(10, 0);
  lcd.print("    ");  // Effacer les anciens chiffres
  lcd.setCursor(10, 0);
  lcd.print(compteur);

  // Affichage sur le moniteur série pour vérification
  Serial.print("Compteur: ");
  Serial.println(compteur);

  delay(100); // Petit délai pour ne pas saturer l'affichage
}


