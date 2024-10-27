<img width="1280" alt="readme-banner" src="https://github.com/user-attachments/assets/35332e92-44cb-425b-9dff-27bcf1023c6c">

# ROCKY FORECAST 🎯

## **Basic Details**  
**Team Name:** AbsurdiTea  

**Team Members:**  
- **Team Lead:** Alita Antony – Jyothi Engineering College  
- **Member 2:** Aditya Manoj – Jyothi Engineering College  

---

## **Project Description**  
### **Why rely on your eyes when you have Rocky Forecast?**  
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
### **ESP8266 Required Libraries in Arduino IDE** 
1. Go to **Tools** > **Board** > **Boards Manager** > *Install esp8266 by ESP8266 Community* > Then select **Generic ESP8266 Module among 'Board' > 'esp8266'**
1. Go to **Tools** > **Board** > **Boards Manager** > *Install esp8266 by ESP8266 Community* > Then select **Generic ESP8266 Module** among **'Board'** > **'esp8266'**
2. Go to the **Library Manager** : Click on **Sketch** > **Include Library** > **Manage Libraries**
In the Library Manager, type **"PubSubClient"** into the search bar.
Find the **"PubSubClient" by Nick O'Leary** and click the Install button.

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
### ***ESP8266 Code for Detection** 
```cpp
// Pin assignments using GPIO numbers
const int s0 = 5;  // GPIO 5 (D1)
const int s1 = 4;  // GPIO 4 (D2)
const int out = 15; // GPIO 15 (D8)
const int s2 = 0;  // GPIO 0 (D3)
const int s3 = 2;  // GPIO 2 (D4)

int red, blue, green;

void setup() {  
  Serial.begin(9600); 
  
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  

  // Set frequency scaling (recommended settings)
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
}  

void loop() {  
  color();
  delay(500);
}

void color() {    
  // Read red
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  delay(50); 
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  // Read blue
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH); 
  delay(50);  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  // Read green
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);  
  delay(50);  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  
  // Print the RGB values
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(" | Blue: ");
  Serial.print(blue);
  Serial.print(" | Green: ");
  Serial.println(green);

  // Check for rain based on RGB values
  if (red >= 30 && green >= 120 && blue >= 30) {
    Serial.println("Status: It's raining!");
  } else if (red <= 21 && green <= 21 && blue <= 72) {
    Serial.println("Status: It's not raining.");
  } else {
    Serial.println("Status: Not Raining.");
  }
}
```
**
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

<img width="500" alt="readme-banner" src="https://github.com/alitaantony/RockyForecast/blob/main/circuitdiagram.png">
*Describe the connections.*

---

## **Screenshots**  

<img width="1280" alt="readme-banner" src="[https://github.com/user-attachments/assets/35332e92-44cb-425b-9dff-27bcf1023c6c](https://github.com/alitaantony/RockyForecast/blob/main/20241027_163025.jpg)">


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


