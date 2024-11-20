#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include "DHTesp.h"
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
 
// Configurações de WiFi e MQTT
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "esp32_mqtt";
const char *TOPIC_PUBLISH_SENSOR = "fiap/iot/sensors";
 
// Configurações de Hardware
const int DHT_PIN = 15;
const int LedPin = 12;
const int servoPin = 14;
const int LDR_PIN = 2;
const int TAMANHO_JSON = 100;
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHTesp dhtSensor;
Servo servo;
 
WiFiClient espClient;
PubSubClient MQTT(espClient);
 
void setup() {
  
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
 
  
  Serial.begin(9600);
 
  // Configura o LED e o servo
  pinMode(LedPin, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  servo.attach(servoPin, 500, 2400);
 
  // Inicializa o LCD
  lcd.init();
  lcd.backlight();
 
  
  initWiFi();
 
  
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
}
 
void loop() {
 
  if (!MQTT.connected()) {
    reconnectMQTT();
  }
 
  // Obter dados dos sensores
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temperatura = data.temperature;
  float umidade = data.humidity;
  int luminosidade = digitalRead(LDR_PIN); // Leitura digital da luminosidade
  
  
  if (luminosidade == HIGH) {
    luminosidade = 0; // Simulação de baixa luminosidade (digitalRead HIGH)
  } else {
    luminosidade = 4095; // Simulação de alta luminosidade (digitalRead LOW)
  }
 
  // Cria um documento JSON para armazenar os dados
  StaticJsonDocument<TAMANHO_JSON> json;
  json["temperatura"] = temperatura;
  json["umidade"] = umidade;
  json["luminosidade"] = luminosidade;  
 
  // Serializa o JSON e envia via Serial
  serializeJson(json, Serial);
  Serial.println();
 
  // Atualiza o display LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umid: ");
  lcd.print(umidade);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print("C");
 
  // Publica os dados no MQTT
  publishSensorData(json);
 

  if (luminosidade > 500) { // Luminosidade alta
    digitalWrite(LedPin, LOW);  // Desliga o LED
  } else { // Luminosidade baixa
    digitalWrite(LedPin, HIGH);  // Liga o LED
  }
 
  
  if (umidade < 50) {
    servo.write(90);  // Abre a válvula
    lcd.setCursor(0, 1);
    lcd.print("Valvula: ABERTA ");
  } else {
    servo.write(180); // Fecha a válvula
    lcd.setCursor(0, 1);
    lcd.print("Valvula: FECHADA");
  }
 

  delay(1000);
}
 
void publishSensorData(StaticJsonDocument<TAMANHO_JSON> &json) {
  char buffer[200];
  serializeJson(json, buffer);
 
  // Publica os dados no tópico MQTT
  if (MQTT.publish(TOPIC_PUBLISH_SENSOR, buffer)) {
    Serial.println("Dados enviados ao MQTT:");
    Serial.println(buffer);
  } else {
    Serial.println("Falha ao enviar dados ao MQTT.");
  }
}
 
void initWiFi() {
  Serial.print("Conectando à rede WiFi: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
 
  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}
 
void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando conectar ao MQTT Broker...");
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao MQTT Broker!");
    } else {
      Serial.println("Falha na conexão. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}