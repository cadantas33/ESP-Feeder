#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BusIO_Register.h>
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

const int pinServo = 4;
const int pinSensor = 17;
const int echoPin = 26;
const int trigPin = 25;
long distancia;
long duracao;
const char* ssid = "Rede";
const char* password = "Senha";

const char* ENTRADA_1 = "Hora 1";
const char* ENTRADA_2 = "Minuto 1";
const char* ENTRADA_3 = "Hora 2";
const char* ENTRADA_4 = "Minuto 2";
const char* ENTRADA_5 = "Hora 3";
const char* ENTRADA_6 = "Minuto 3";

Ultrasonic ultra(trigPin, echoPin);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
    <title>Entradad de Horários</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    </head><body>
    <div style="display: flex;">
      <form action="/get">
        Hora 1: <input type="text" name="Hora 1">
        <input type="submit" value="Enviar">
      </form>
      <form action="/get">
        Minuto 1: <input type="text" name="Minuto 1">
        <input type="submit" value="Enviar">
      </form>
    </div>
    <br>
    <div style="display: flex;">
    <form action="/get">
      Hora 2: <input type="text" name="Hora 2">
      <input type="submit" value="Enviar">
    </form>
    <form action="/get">
        Minuto 2: <input type="text" name="Minuto 2">
        <input type="submit" value="Enviar">
      </form>
    </div>
    <br>
    <div style="display: flex;">
      <form action="/get">
        Hora 3: <input type="text" name="Hora 3">
        <input type="submit" value="Enviar">
      </form>
      <form action="/get">
        Minuto 3: <input type="text" name="Minuto 3">
        <input type="submit" value="Enviar">
      </form>
    </div>
  </body></html>)rawliteral";

void ultrassonico();
void infraRed();

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
  ultrassonico();

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

void ultrassonico() {

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


}