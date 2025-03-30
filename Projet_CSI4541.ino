#include <Servo.h> // On inclut la bibliothèque Servo pour contrôler les servomoteurs

// On déclare deux objets de type Servo pour contrôler les moteurs gauche et droit
Servo moteurG;
Servo moteurD;

// On définit les numéros des broches de l’Arduino auxquelles les composants sont connectés
#define PIN_MOTEUR_G 5   // Broche du moteur gauche
#define PIN_MOTEUR_D 6   // Broche du moteur droit
#define TRIG_PIN 8       // Broche de commande TRIG du capteur HC-SR04
#define ECHO_PIN 7       // Broche de réception ECHO du capteur HC-SR04

void setup() {
  // On attache les objets Servo à leurs broches respectives
  moteurG.attach(PIN_MOTEUR_G);
  moteurD.attach(PIN_MOTEUR_D);

  // On configure la broche TRIG comme sortie : on enverra un signal dessus
  pinMode(TRIG_PIN, OUTPUT);

  // On configure la broche ECHO comme entrée : on lira le signal de retour dessus
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duree;      // On va stocker ici la durée du signal reçu (en microsecondes)
  int distance;    // Et ici, la distance calculée (en centimètres)

  // *** Mesure de la distance à l’aide du capteur ultrason HC-SR04 ***

  // On s'assure que le TRIG est à l'état bas pendant 2 microsecondes
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // On envoie un signal de 10 microsecondes sur la broche TRIG
  // Cela déclenche l'émission d'une onde ultrasonore
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  // On repasse TRIG à l'état bas
  digitalWrite(TRIG_PIN, LOW);

  // On mesure le temps que met l'onde à revenir (durée du signal HIGH sur ECHO)
  duree = pulseIn(ECHO_PIN, HIGH);

  // On convertit cette durée en distance (en centimètres)
  // Formule : distance = (durée * vitesse du son) / 2
  distance = duree * 0.034 / 2;

  // *** Réaction du robot en fonction de la distance mesurée ***

  if (distance < 15) {
    // Si un obstacle est détecté à moins de 15 cm :
    // On arrête les deux moteurs en envoyant une impulsion neutre (90°)
    moteurG.write(90);
    moteurD.write(90);
    delay(500); // On attend un peu pour stabiliser la situation
  } else {
    // Sinon, on fait avancer le robot :
    // Le moteur gauche tourne à fond en avant (180°)
    // Le moteur droit tourne à fond en arrière (0°)
    moteurG.write(180);
    moteurD.write(0);
  }

  // Petite pause avant la prochaine mesure
  delay(200);
}
