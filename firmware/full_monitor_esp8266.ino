// Anexo 24: Código para el Sistema de Monitoreo con ESP8266 y Pantalla OLED

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define DHTTYPE DHT11
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE);
const char* ssid = "Redes_UACM";
const char* password = "ISETUACM";
const char* host = "187.251.123.93";
const int port = 8112;
const int watchdog = 300000;
unsigned long previousMillis = 0;
typedef struct struct_message {
int a_1;
float b_1;
float c_1;
} struct_message;
struct_message myData;
int Sensor[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
float Temp[16];
float Hum[16];
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
memcpy(&myData, incomingData, sizeof(myData));
int sensorIndex = myData.a_1 - 1;
if (sensorIndex >= 0 && sensorIndex < 16) {
Temp[sensorIndex] = myData.b_1;
Hum[sensorIndex] = myData.c_1;
}
}
void setup() {
Serial.begin(115200);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("\nWiFi connected");  
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
dht.begin();
if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
Serial.println(F("SSD1306 allocation failed"));
for(;;);
}
display.clearDisplay();
WiFi.mode(WIFI_STA);
if (esp_now_init() != 0) {
Serial.println("Error initializing ESP-NOW");
return;
}
esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
unsigned long currentMillis = millis();
if (currentMillis - previousMillis > watchdog) {
previousMillis = currentMillis;
WiFiClient client;
if (!client.connect(host, port)) {
Serial.println("Fallo al conectar");
return;
}
String url = "/home.php?";
for (int i = 0; i < 16; i++) {
url += "temp" + String(i+1) + "=" + Temp[i];
url += "&hum" + String(i+1) + "=" + Hum[i];
if (i < 15) url += "&";
}
client.print(String("GET ") + url + " HTTP/1.1\r\n" +
"Host: " + host + "\r\n" +
"Connection: close\r\n\r\n");
delay(10);
while(client.available()) {
String line = client.readStringUntil('\r');
Serial.print(line);
}
}
for (int i = 0; i < 16; i++) {
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(40,5);
display.println("SENSOR:");
display.setCursor(90,5);
display.println(Sensor[i]);
display.setCur
