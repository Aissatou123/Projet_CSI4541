#include <Servo.h>  // Inclusion de la bibliothèque Servo pour contrôler les moteurs

Servo moteurG;  // Déclaration du moteur gauche
Servo moteurD;  // Déclaration du moteur droit

#define PIN_MOTEUR_G 5  // Pin de commande du moteur gauche
#define PIN_MOTEUR_D 6  // Pin de commande du moteur droit
#define TRIG_PIN 8      // Pin TRIG du capteur à ultrasons
#define ECHO_PIN 7      // Pin ECHO du capteur à ultrasons

void setup() {
  moteurG.attach(PIN_MOTEUR_G);  // Association du moteur gauche à sa broche
  moteurD.attach(PIN_MOTEUR_D);  // Association du moteur droit à sa broche
  pinMode(TRIG_PIN, OUTPUT);     // Configuration de la broche TRIG en sortie
  pinMode(ECHO_PIN, INPUT);      // Configuration de la broche ECHO en entrée
}

void loop() {
  long duree;     // Variable pour stocker la durée du signal
  int distance;   // Variable pour stocker la distance calculée

  // Envoi d'une impulsion ultrasonique
  digitalWrite(TRIG_PIN, LOW);     // S'assurer que TRIG est LOW
  delayMicroseconds(2);            // Pause courte
  digitalWrite(TRIG_PIN, HIGH);    // Envoi d'une impulsion HIGH pendant 10 µs
  delayMicroseconds(10);           
  digitalWrite(TRIG_PIN, LOW);     // Fin de l'impulsion

  // Lecture de la durée du retour de l'onde ultrasonique
  duree = pulseIn(ECHO_PIN, HIGH); // Mesure du temps que met l'onde à revenir

  // Calcul de la distance à partir de la durée
  distance = duree * 0.034 / 2;    // Vitesse du son = 0.034 cm/µs

  if (distance < 15) {
    // Si un obstacle est détecté à moins de 15 cm :
    moteurG.write(90);  // Arrêt du moteur gauche
    moteurD.write(90);  // Arrêt du moteur droit
    delay(300);         // Petite pause

    // Demi-tour (pivot sur place)
    moteurG.write(0);    // Moteur gauche recule
    moteurD.write(180);  // Moteur droit avance
    delay(600);          // Durée suffisante pour se réorienter

    // Pause avant de repartir
    moteurG.write(90);  // Arrêt
    moteurD.write(90);
    delay(300);
  } else {
    // Sinon, avancer en ligne droite
    moteurG.write(180);  // Moteur gauche avance
    moteurD.write(180);  // Moteur droit avance
  }

  delay(100);  // Attente avant la prochaine mesure
}
