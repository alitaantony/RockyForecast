import paho.mqtt.client as mqtt
from RPLCD.i2c import CharLCD

# Initialize the LCD
lcd = CharLCD('PCF8574', 0x27)  # Adjust I2C address if needed

# Callback function for when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    print("Connected with result code", rc)
    client.subscribe("weather/status")  # Subscribe to the topic

# Callback function for when a message is received
def on_message(client, userdata, msg):
    lcd.clear()  # Clear the LCD display
    lcd.write_string(f"Status: {msg.payload.decode()}")  # Display the message

# Set up the MQTT client
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# Connect to the MQTT broker
client.connect("localhost", 1883, 60)  # Connect to the broker running on the same Raspberry Pi

# Start the loop to process incoming messages
client.loop_forever()