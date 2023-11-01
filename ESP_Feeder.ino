#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <RTClib.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include <LiquidCrystal.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

Servo servo;
RTC_DS1307 rtc;
LiquidCrystal lcd (22, 21, 5, 18, 23, 19);
Ultrasonic ultra(trigPin, echoPin);

const int pinServo = 4;
const int pinSensor = 17;
const int echoPin = 26;
const int trigPin = 25;
long distancia;
long duracao;

const char* ssid = "Rede";
const char* password = "Senha";


void distanceCalc();
void infraRed();
void levelCheck();

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  servo.attach(pinServo);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinSensor, INPUT);
  Wire.begin(15, 2);
  if (! rtc.begin()) {
    Serial.println("RTC nao encontrado");
    while (1);
  }
  if (! rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  void distanceCalc();
  void infraRed();
  void levelCheck();

  lcd.clear();

  DateTime now = rtc.now(); //Faz a leitura da data e hora atual, guarda na função now 

  Serial.println("Ano: "); //Bloco para escrever data e hora atuais no monitor serial 
  Serial.println(now.year(), DEC);
  Serial.println("Mes: ");
  Serial.println(now.month(), DEC);
  Serial.println("Dias: ");
  Serial.println(now.day(), DEC);
  Serial.println("Horas: ");
  Serial.println(now.hour(), DEC);
  Serial.println("Minutos: ");
  Serial.println(now.minute(), DEC);
  Serial.println("Segundos: ");
  Serial.println(now.second(), DEC);
  delay(1000);

  if(now.hour() == "variavel_hora" && now.minute() == "variavel_minutos"){
    servo.write(90);
  }
  
}

void distanceCalc() {

  digitalWrite(trigPin, LOW); //Pulsando o sensor ultrassônico 
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao / 58; //Calculando distancia 


void infraRed(){
   do{
    servo.write(0);
  }while(digitalRead(pinSensor) == HIGH);
}

void levelCheck(){
  if (distancia >= 50 && distancia <= 60) {
    lcd.setCursor(0, 0);
    lcd.print("Cheio");
    delay(500);
  } else if (distancia < 50 && distancia >= 30) {
    lcd.setCursor(0, 0);
    lcd.print("Pela metade");
    delay(500);
  } else if (distancia < 30 && distancia >= 10) {
    lcd.setCursor(0, 0);
    lcd.print("Quase vazio");
    delay(500);
  } else if (distancia < 10) {
    lcd.setCursor(0, 0);
    lcd.print("Vazio");
    delay(500);
  }
}


}
