#include "DHTesp.h"
#include <ArduinoJson.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

// Configurações de Hardware
const int DHT_PIN = 15;
const int LedPin = 12;
const int servoPin = 14;
const int LDR_PIN = 2;
const int TAMANHO_JSON = 100;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHTesp dhtSensor;
Servo servo;

void setup() {
  // Inicia o sensor DHT
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // Inicia a comunicação serial
  Serial.begin(9600);

  // Configura o LED e o servo
  pinMode(LedPin, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  servo.attach(servoPin, 500, 2400);

  // Inicializa o LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Cria um documento JSON para armazenar os dados
  StaticJsonDocument<TAMANHO_JSON> json;

  // Faz a leitura dos valores de temperatura, umidade e luminosidade
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temperatura = data.temperature;
  float umidade = data.humidity;
  int luminosidade = analogRead(LDR_PIN);

  // Armazena os valores no JSON
  json["temperatura"] = temperatura;
  json["umidade"] = umidade;
  json["luminosidade"] = luminosidade;

  // Serializa o JSON e envia via Serial
  serializeJson(json, Serial);
  Serial.println();

  // Atualiza o display LCD com os valores
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umid: ");
  lcd.print(umidade);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print("C");

  // Lógica para o LED e o servo com base na leitura do LDR e umidade
  if (luminosidade < 500) {
    digitalWrite(LedPin, LOW);  // Liga o LED
  } else {
    digitalWrite(LedPin, HIGH); // Desliga o LED
  }

  if (umidade < 50) {
    servo.write(90);  // Abre a válvula
    lcd.setCursor(0, 1);
    lcd.print("Valvula: ABERTA");
  } else {
    servo.write(180); // Fecha a válvula
    lcd.setCursor(0, 1);
    lcd.print("Valvula: FECHADA");
  }

  delay(500);
}
