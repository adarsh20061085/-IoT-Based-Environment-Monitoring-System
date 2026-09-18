#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =========================
// Wi-Fi
// =========================
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// =========================
// Pin Configuration
// =========================
#define DHTPIN 4
#define DHTTYPE DHT11

#define MQ135_PIN 34
#define MQ2_PIN   35

#define GREEN_LED 26
#define RED_LED   27
#define BUZZER    25

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// =========================
// Objects
// =========================
DHT dht(DHTPIN, DHTTYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

WebServer server(80);

// =========================
// Variables
// =========================
float temperature = 0;
float humidity = 0;

int airQuality = 0;
int gasLevel = 0;

bool alertState = false;

// =========================
// Web Page
// =========================
String createWebPage()
{
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">

<title>IoT Environment Monitor</title>

<style>

body {
  font-family: Arial, sans-serif;
  background: #f2f2f2;
  text-align: center;
  margin: 0;
}

.header {
  background: #222;
  color: white;
  padding: 20px;
}

.container {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  gap: 15px;
  padding: 25px;
}

.card {
  background: white;
  width: 220px;
  padding: 20px;
  border-radius: 12px;
  box-shadow: 0 3px 10px rgba(0,0,0,0.15);
}

.value {
  font-size: 32px;
  font-weight: bold;
}

.status {
  font-size: 22px;
  font-weight: bold;
}

</style>

<script>

function updateData()
{
  fetch('/data')
  .then(response => response.json())
  .then(data => {

    document.getElementById("temperature").innerHTML =
      data.temperature + " °C";

    document.getElementById("humidity").innerHTML =
      data.humidity + " %";

    document.getElementById("air").innerHTML =
      data.air;

    document.getElementById("gas").innerHTML =
      data.gas;

    document.getElementById("status").innerHTML =
      data.status;

  });
}

setInterval(updateData, 2000);

</script>

</head>

<body>

<div class="header">

<h1>🌍 IoT Environment Monitor</h1>

<p>ESP32 Environmental Monitoring System</p>

</div>

<div class="container">

<div class="card">
<h2>🌡️ Temperature</h2>
<div class="value" id="temperature">--</div>
</div>

<div class="card">
<h2>💧 Humidity</h2>
<div class="value" id="humidity">--</div>
</div>

<div class="card">
<h2>🌫️ Air Quality</h2>
<div class="value" id="air">--</div>
</div>

<div class="card">
<h2>🛢️ Gas Level</h2>
<div class="value" id="gas">--</div>
</div>

<div class="card">

<h2>System Status</h2>

<div class="status" id="status">
Checking...
</div>

</div>

</div>

</body>
</html>
)rawliteral";

  return html;
}

// =========================
// Handle Web Page
// =========================

void handleRoot()
{
  server.send(
    200,
    "text/html",
    createWebPage()
  );
}

// =========================
// Send Sensor Data
// =========================

void handleData()
{
  String status;

  if (alertState)
  {
    status = "ALERT";
  }
  else
  {
    status = "NORMAL";
  }

  String json = "{";

  json += "\"temperature\":";
  json += String(temperature, 1);

  json += ",\"humidity\":";
  json += String(humidity, 1);

  json += ",\"air\":";
  json += String(airQuality);

  json += ",\"gas\":";
  json += String(gasLevel);

  json += ",\"status\":\"";
  json += status;

  json += "\"}";

  server.send(
    200,
    "application/json",
    json
  );
}

// =========================
// OLED Display
// =========================

void updateOLED()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("ENVIRONMENT MONITOR");

  display.setCursor(0, 15);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 27);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0, 39);
  display.print("Air: ");
  display.println(airQuality);

  display.setCursor(0, 51);

  if (alertState)
  {
    display.println("STATUS: ALERT");
  }
  else
  {
    display.println("STATUS: NORMAL");
  }

  display.display();
}

// =========================
// Setup
// =========================

void setup()
{
  Serial.begin(115200);

  // Pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  // Start DHT
  dht.begin();

  // Start OLED
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C))
  {
    Serial.println("OLED not found!");

    while (true);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 20);
  display.println("Starting System...");

  display.display();

  delay(2000);

  // Wi-Fi
  WiFi.begin(
    ssid,
    password
  );

  display.clearDisplay();

  display.setCursor(0, 20);
  display.println("Connecting WiFi...");

  display.display();

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi Connected!");

  Serial.print("ESP32 IP Address: ");

  Serial.println(
    WiFi.localIP()
  );

  display.clearDisplay();

  display.setCursor(0, 15);
  display.println("WiFi Connected");

  display.setCursor(0, 30);

  display.println(
    WiFi.localIP()
  );

  display.display();

  delay(3000);

  // Web server
  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/data",
    handleData
  );

  server.begin();

  Serial.println("Web server started");
}

// =========================
// Main Loop
// =========================

void loop()
{
  server.handleClient();

  // Read DHT
  float newTemperature =
    dht.readTemperature();

  float newHumidity =
    dht.readHumidity();

  if (!isnan(newTemperature))
  {
    temperature =
      newTemperature;
  }

  if (!isnan(newHumidity))
  {
    humidity =
      newHumidity;
  }

  // Read MQ sensors
  airQuality =
    analogRead(MQ135_PIN);

  gasLevel =
    analogRead(MQ2_PIN);

  // =========================
  // Alert Threshold
  // =========================

  if (
      airQuality > 2500 ||
      gasLevel > 2500
     )
  {
    alertState = true;

    digitalWrite(
      RED_LED,
      HIGH
    );

    digitalWrite(
      GREEN_LED,
      LOW
    );

    digitalWrite(
      BUZZER,
      HIGH
    );
  }
  else
  {
    alertState = false;

    digitalWrite(
      RED_LED,
      LOW
    );

    digitalWrite(
      GREEN_LED,
      HIGH
    );

    digitalWrite(
      BUZZER,
      LOW
    );
  }

  // OLED
  updateOLED();

  // Serial Monitor
  Serial.println(
    "-------------------------"
  );

  Serial.print(
    "Temperature: "
  );

  Serial.print(
    temperature
  );

  Serial.println(" C");

  Serial.print(
    "Humidity: "
  );

  Serial.print(
    humidity
  );

  Serial.println(" %");

  Serial.print(
    "Air Quality: "
  );

  Serial.println(
    airQuality
  );

  Serial.print(
    "Gas Level: "
  );

  Serial.println(
    gasLevel
  );

  Serial.print(
    "Status: "
  );

  Serial.println(
    alertState ?
    "ALERT" :
    "NORMAL"
  );

  delay(2000);
}
