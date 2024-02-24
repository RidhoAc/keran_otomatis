//library
#include <Servo.h>
  Servo myservo;

//Deklarasi variabel
const int pinTRIGGER = 9;
const int pinECHO = 8;
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int pirPin = 6;
const int servoPin = 10; 
int pirstat, servostat;
float durasi, jarak, jarak1, jarak2, jarakf;
const int long interval = 5*60000;
unsigned long prevMillis;
unsigned long currentMillis;
unsigned long counter;

void setup() {
  // Mengatur mode pin
  Serial.begin (9600);
  pinMode (pinTRIGGER, OUTPUT);
  pinMode (pinECHO, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  myservo.attach(servoPin);
  myservo.write(0);
  prevMillis = 0; 
  counter = 0; 
}

void loop() {
  digitalWrite(pinTRIGGER, HIGH); //Menyalakan gelombang ultrasonik
  delayMicroseconds(100);
  digitalWrite(pinTRIGGER, LOW); //Mematikan gelombang ultrasonik

  durasi = pulseIn(pinECHO, HIGH); //Menghitung durasi
  jarak = ((durasi*0.034)/2); //Menghitung jarak
  jarak1 = jarak;
  delay(150);
  
  digitalWrite(pinTRIGGER, HIGH); //Menyalakan gelombang ultrasonik
  delayMicroseconds(100);
  digitalWrite(pinTRIGGER, LOW); //Mematikan gelombang ultrasonik
  durasi = pulseIn(pinECHO, HIGH); //Menghitung durasi
  jarak = ((durasi*0.034)/2); //Menghitung jarak
  jarak2 = jarak;
  
  jarakf = abs(jarak1-jarak2);
  if (jarakf >= 0 && jarakf <= 0.5){
    jarak = 1.0054*jarak1+0.3638;
  }
  else {
    jarak = 0;
  }

  pirstat = digitalRead(pirPin);
  
  if (jarak > 0 && jarak <= 7 && pirstat == 1){
    myservo.write(0);
    servostat = 0;
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
  if (jarak > 7 && jarak <= 12 && pirstat == 1){
    myservo.write(300);
    servostat = 1;
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
  if (jarak > 12 && jarak <= 17 && pirstat == 1){
    myservo.write(60);
    servostat = 2;
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  }
  if (jarak > 17 && jarak <= 22 && pirstat == 1){
    myservo.write(90);
    servostat = 3;
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  }
  if (pirstat == 0){
    myservo.write(90);
    servostat = 0;
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }

  if (servostat == 0){
    counter = 0;
  }

  if (counter == 0 && servostat > 0 && jarak > 22){
    counter = 1;
  }
  if (counter == 1){
    currentMillis = millis();
  }
  if (currentMillis >= (millis() + interval)){
    myservo.write(0);
    servostat = 0;
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    counter = 0;
  }
  
  delay(150);
}           
