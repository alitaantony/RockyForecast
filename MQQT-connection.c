#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "your_SSID";       
const char* password = "your_PASSWORD";
const char* mqtt_server = "192.168.24.22";  // Raspberry Pi IP

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Set the MQTT broker server
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    client.connect("ESP8266Client");
  }
  client.loop();
  
  // Send the status (Raining or Not Raining)
  client.publish("weather/status", "Raining");  // Example data
  delay(5000);  // Publish every 5 seconds
}
