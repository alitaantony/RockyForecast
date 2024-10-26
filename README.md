<img width="1280" alt="readme-banner" src="https://github.com/user-attachments/assets/35332e92-44cb-425b-9dff-27bcf1023c6c">
---

# ROCKY FORECAST 🎯

## **Basic Details**  
**Team Name:** AbsurdiTea  

**Team Members:**  
- **Team Lead:** Alita Antony – Jyothi Engineering College  
- **Member 2:** Aditya Manoj – Jyothi Engineering College  

---

## **Project Description**  
**Why rely on your eyes when you have Rocky Forecast?**  
With our never-before-discovered **water-induced Stone Darkening Property™** and a clever color sensor, you’ll finally know if it's raining—because obviously, **who could tell otherwise?**

### **The Problem (that doesn’t exist):**  
In a world overflowing with gadgets, we face a crisis: **how do we know if it’s raining without looking outside?** Enter **Rocky Forecast**—using the color-changing magic of granite, we bring clarity to the wet world! Now, no need to peek through the drizzle—just ask your trusty Rocky.

### **The Solution (that nobody asked for):**  
Place this marvelous rock outside, and when rain hits, it darkens to announce the wetness. Why trust your instincts when a **stone** can do it for you? With Rocky, you'll know when to leave that umbrella behind!

---

## **Technical Details**

### **Technologies/Components Used**

**Software:**  
- Languages: C++, Python  
- Tools: Arduino IDE, Raspberry Pi OS  
- MQTT protocol for communication between ESP8266 and Raspberry Pi  

**Hardware:**  
- **ESP8266 (NodeMCU)**  
- **Raspberry Pi 4 Model B**  
- **Color Sensor** (to detect rain-induced changes on the granite)  
- **16x2 I2C LCD** (for displaying rain status)  

---

## **Implementation**

### **Installation on Raspberry Pi**  
1. **Update packages**:
   ```bash
   sudo apt update && sudo apt upgrade
   ```
2. **Install MQTT Broker**:
   ```bash
   sudo apt install mosquitto mosquitto-clients
   sudo systemctl start mosquitto
   ```
3. **Enable I2C**:
   ```bash
   sudo raspi-config
   ```
   - Go to **Interfacing Options** > **I2C** and enable it.  
   - Install necessary libraries:
     ```bash
     sudo apt install python3-smbus i2c-tools
     pip3 install RPLCD paho-mqtt
     ```

### **ESP8266 Code**  
The ESP8266 publishes the rain status via MQTT to the Raspberry Pi:

```cpp
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* mqtt_server = "192.168.24.22";  // Replace with your Pi’s IP

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    client.connect("ESP8266Client");
  }
  client.loop();
  client.publish("weather/status", "Raining");
  delay(5000);
}
```

---

### **Python Script on Raspberry Pi**  
Create a script to display rain status on the **LCD**.

```python
import paho.mqtt.client as mqtt
from RPLCD.i2c import CharLCD

lcd = CharLCD('PCF8574', 0x27)  # Adjust I2C address if needed

def on_connect(client, userdata, flags, rc):
    print("Connected with result code", rc)
    client.subscribe("weather/status")

def on_message(client, userdata, msg):
    lcd.clear()
    lcd.write_string(f"Status: {msg.payload.decode()}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("localhost", 1883, 60)
client.loop_forever()
```

---

## **Schematic & Circuit**  
- **ESP8266** connects to Wi-Fi and sends MQTT data.  
- **Raspberry Pi** receives the message and updates the **I2C LCD** with rain status.

![Circuit Diagram](Add your circuit diagram here)  
*Describe the connections.*

---

## **Screenshots**  
![Screenshot1](Add screenshot 1)  
*Caption explaining the screenshot.*  

![Screenshot2](Add screenshot 2)  
*Caption explaining the screenshot.*

---

## **Demo Video**  
[Add your demo video link here]  
*Describe the demo briefly.*

---

## **Team Contributions**
- **Alita Antony**: Code and hardware implementation  
- **Aditya Manoj**: Documentation and debugging  

---

**Made with ❤️ at TinkerHub Useless Projects**  

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)  
![Static Badge](https://img.shields.io/badge/UselessProject--24-24?link=https%3A%2F%2Fwww.tinkerhub.org%2Fevents%2FQ2Q1TQKX6Q%2FUseless%2520Projects)

---


