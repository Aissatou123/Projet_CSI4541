#include <Servo.h>

Servo moteurG;
Servo moteurD;

#define PIN_MOTEUR_G 5
#define PIN_MOTEUR_D 6
#define trigPin 9
#define echoPin 10

void setup() {
  Serial.begin(9600);
  moteurG.attach(PIN_MOTEUR_G);
  moteurD.attach(PIN_MOTEUR_D);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 30) {
    Serial.println("Obstacle détecté ! Arrêt du robot.");
    moteurG.write(90); // Stop
    moteurD.write(90);
  } else {
    Serial.println("Le robot avance !");
    moteurG.write(180);
    moteurD.write(0);
  }
  delay(300);
}
