🌍 IoT-Based Environment Monitoring System

An IoT-based Environment Monitoring System that uses sensors and an ESP32 to monitor environmental conditions such as temperature, humidity, air quality, and gas levels. The collected data can be sent over Wi-Fi and displayed on an online/web dashboard.

---

📌 Project Overview

The main purpose of this project is to monitor environmental conditions in real time using sensors connected to an ESP32.

The ESP32 collects sensor data and sends it through Wi-Fi to a web/cloud platform, where the information can be monitored remotely.

🔄 Working

Environmental Sensors
        ↓
      ESP32
        ↓
      Wi-Fi
        ↓
 Cloud / Web Server
        ↓
   Web Dashboard

---

✨ Features

- 🌡️ Real-time temperature monitoring
- 💧 Humidity monitoring
- 🌫️ Air-quality monitoring
- 🛢️ Gas-level detection
- 📡 Wi-Fi connectivity
- 📊 Online/web dashboard
- 🔔 Alert system for abnormal readings
- 💻 Remote monitoring
- 📈 Data visualization

---

🛠️ Components Required

Component| Quantity| Purpose
ESP32| 1| Main IoT controller
DHT11/DHT22| 1| Temperature & humidity
MQ-135| 1| Air-quality monitoring
MQ-2| 1| Gas/smoke detection
OLED Display| 1| Display sensor readings
Buzzer| 1| Alert indication
LED| 1–2| Status indication
Resistor| As required| Circuit protection
Breadboard| 1| Circuit assembly
Jumper Wires| As required| Connections
USB Cable| 1| Programming/power

---

💻 Technologies Used

Hardware

- ESP32
- DHT11/DHT22
- MQ-135
- MQ-2
- OLED Display

Software

- Arduino IDE
- C/C++
- HTML
- CSS
- JavaScript

IoT

- Wi-Fi
- Cloud/Web Server
- REST API or Firebase

---

🔌 Basic Circuit Connections

DHT11/DHT22

DHT Sensor       ESP32

VCC       →      3.3V
GND       →      GND
DATA      →      GPIO 4

OLED Display

OLED             ESP32

VCC       →      3.3V
GND       →      GND
SDA       →      GPIO 21
SCL       →      GPIO 22

MQ Sensor

MQ Sensor        ESP32

VCC       →      Suitable supply
GND       →      GND
AO        →      ESP32 Analog GPIO

«⚠️ Check the output voltage of your particular MQ module before connecting its analog output directly to an ESP32 ADC pin. ESP32 GPIOs are not 5V tolerant.»

---

⚙️ How It Works

1. The sensors measure environmental conditions.
2. The ESP32 reads the sensor values.
3. The ESP32 processes the collected data.
4. The ESP32 connects to Wi-Fi.
5. Sensor readings are sent to the cloud/web server.
6. The web dashboard displays the readings.
7. If a value crosses a defined threshold, an alert can be generated.

---

📊 Example Dashboard

-----------------------------------------
       ENVIRONMENT MONITORING
-----------------------------------------

Temperature       28.5 °C

Humidity          65 %

Air Quality       Good

Gas Level         Normal

-----------------------------------------
       System Status: ONLINE
-----------------------------------------

---

📁 Project Structure

iot-environment-monitoring/
│
├── README.md
│
├── firmware/
│   └── environment_monitor.ino
│
├── circuit/
│   └── circuit_diagram.png
│
├── dashboard/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
├── images/
│   ├── prototype.jpg
│   └── dashboard.jpg
│
└── documentation/
    └── project_report.pdf

---

📚 Arduino Libraries

The following libraries may be required:

- "DHT sensor library"
- "Adafruit Unified Sensor"
- "Adafruit GFX"
- "Adafruit SSD1306"
- "WiFi"
- "HTTPClient"
- "ArduinoJson"

Install the required libraries through:

Arduino IDE → Library Manager

---

🚀 Setup Instructions

1. Install Arduino IDE

Install Arduino IDE and add ESP32 board support.

2. Connect the Components

Connect the sensors and OLED according to the circuit diagram.

3. Install Libraries

Install the required libraries using the Arduino Library Manager.

4. Configure Wi-Fi

Add your Wi-Fi credentials to the ESP32 code.

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

Do not upload real Wi-Fi passwords or API keys to GitHub.

5. Upload the Code

Connect the ESP32 to your computer and upload the firmware.

6. Monitor the Data

Open the Serial Monitor to check the sensor readings and Wi-Fi connection.

7. Open the Dashboard

Open the web dashboard to monitor environmental conditions remotely.

---

🔐 Security

For a real deployment:

- Don't upload Wi-Fi passwords to GitHub.
- Don't upload Firebase credentials/API keys.
- Use environment variables or a separate configuration file.
- Add authentication to the dashboard.
- Use HTTPS for communication where supported.

---

🔮 Future Improvements

- 📱 Android/mobile application
- ☁️ Cloud data storage
- 📊 Historical graphs
- 📧 Email alerts
- 🔔 Real-time notifications
- 🌐 Multiple monitoring stations
- 🔋 Solar-powered version
- 🗺️ GPS-based environmental monitoring
- 🤖 AI-based pollution prediction
- 📈 Long-term environmental data analysis

---

🎯 Applications

This system can be used for:

- Homes
- Classrooms
- Laboratories
- Offices
- Industrial areas
- Greenhouses
- Smart cities
- Environmental monitoring stations

---

👨‍💻 Project Author

Adarsh Kumar Sah

B.Tech — Electronics & Communication Engineering

---

⭐ Support

If you find this project useful, consider giving the repository a ⭐ on GitHub.

---

📜 License

This project is open-source and available under the MIT License.
