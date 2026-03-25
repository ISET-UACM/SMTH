// Anexo 24: Código para el Sistema de Monitoreo con ESP8266 y Pantalla OLED
#include <ESP8266WiFi.h>
const char* ssid     = "Redes_UACM";  // SSID
const char* password = "ISETUACM";    // Password
const char* host = "187.251.123.93";  // Server IP
const int   port = 8112;              // Server Port
const int   watchdog = 300000;        // Intervalo de envio (5 minutos)
float Temp[16] = {0};
float Hum[16] = {0};
unsigned long previousMillis = 0;
void setup() {
Serial.begin(115200);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("\nWiFi conectado");
Serial.print("IP local: ");
Serial.println(WiFi.localIP());
}
void loop() {
unsigned long currentMillis = millis();
if (currentMillis - previousMillis > watchdog) {
previousMillis = currentMillis;
enviarDatos();
}
}
void enviarDatos() {
WiFiClient client;
if (!client.connect(host, port)) {
Serial.println("Fallo al conectar con el servidor");
return;
}
String url = "/home.php?";
for (int i = 0; i < 16; i++) {
url += "temp" + String(i+1) + "=" + String(Temp[i]);
url += "&hum" + String(i+1) + "=" + String(Hum[i]);
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
client.stop();
}
