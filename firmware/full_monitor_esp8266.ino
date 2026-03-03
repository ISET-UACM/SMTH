// Anexo 24: Código para el Sistema de Monitoreo con ESP8266 y Pantalla OLED
#include <ESP8266WiFi.h>
#include <espnow.h>
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
    int a_1; // ID Sensor
    float b_1; // Temp
    float c_1; // Hum
} struct_message;

struct_message myData;
float Temp[16];
float Hum[16];

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    memcpy(&myData, incomingData, sizeof(myData));
    int idx = myData.a_1 - 1;
    if (idx >= 0 && idx < 16) {
        Temp[idx] = myData.b_1;
        Hum[idx] = myData.c_1;
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    dht.begin();
    WiFi.mode(WIFI_STA);
    esp_now_init();
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > watchdog) {
        previousMillis = currentMillis;
        // Lógica de envío HTTP GET al servidor
    }
    // Lógica de refresco de pantalla OLED
}
