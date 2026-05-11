#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

// =========================
// WiFi + MQTT
// =========================
const char* ssid       = "Wokwi-GUEST";
const char* password   = "";
const char* mqttServer = "broker.hivemq.com";

const char* topic = "cs423/smartplug/petch_1660702588";

// =========================
// Variables
// =========================
unsigned long lastPublish   = 0;
unsigned long lastReconnect = 0;

float totalKwh  = 0.0;
float totalCost = 0.0;

float maxWatt = 0.0;
String maxLevel = "";

// =========================
// Setup
// =========================
void setup() {

  Serial.begin(115200);

  // WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  // MQTT
  client.setServer(mqttServer, 1883);

  client.setKeepAlive(90);
  client.setSocketTimeout(10);
  client.setBufferSize(256);
}

// =========================
// MQTT Reconnect
// =========================
void reconnectMQTT() {

  if (millis() - lastReconnect < 5000) return;

  lastReconnect = millis();

  Serial.print("Connecting MQTT...");

  String clientId = "ESP32_" + String(random(1000, 9999));

  if (client.connect(clientId.c_str())) {

    Serial.println("OK");

  } else {

    Serial.print("FAILED rc=");
    Serial.println(client.state());
  }
}

// =========================
// Main Loop
// =========================
void loop() {

  // -------------------------
  // WiFi Check
  // -------------------------
  if (WiFi.status() != WL_CONNECTED) {

    WiFi.disconnect();
    WiFi.begin(ssid, password);

    delay(1000);
    return;
  }

  // -------------------------
  // MQTT Check
  // -------------------------
  if (!client.connected()) {

    reconnectMQTT();
    return;
  }

  client.loop();

  // -------------------------
  // Publish Every 5 Seconds
  // -------------------------
  if (millis() - lastPublish >= 5000) {

    lastPublish = millis();

    // Simulated Current
    float amp = (analogRead(34) / 4095.0) * 15.0;

    // Calculate Watt
    float watt = amp * 220.0;

    // kWh Calculation
    totalKwh += (watt / 1000.0) * (5.0 / 3600.0);

    // Electricity Cost
    totalCost = totalKwh * 4.5;

    // -------------------------
    // Power Level Analysis
    // -------------------------
    String level;

    if (watt < 100)
      level = "Standby";
    else if (watt < 500)
      level = "Low";
    else if (watt < 1000)
      level = "Medium";
    else if (watt < 2000)
      level = "High";
    else
      level = "VeryHigh";

    // -------------------------
    // Track Highest Usage
    // -------------------------
    if (watt > maxWatt) {
      maxWatt = watt;
      maxLevel = level;
    }

    // -------------------------
    // JSON Payload
    // -------------------------
    char payload[256];

    snprintf(payload, sizeof(payload),
      "{\"watt\":%.1f,"
      "\"amp\":%.2f,"
      "\"level\":\"%s\","
      "\"kwh\":%.4f,"
      "\"cost\":%.2f,"
      "\"max_watt\":%.1f,"
      "\"max_level\":\"%s\"}",
      watt,
      amp,
      level.c_str(),
      totalKwh,
      totalCost,
      maxWatt,
      maxLevel.c_str()
    );

    // -------------------------
    // Publish
    // -------------------------
    bool ok = client.publish(topic, payload);

    if (ok) {
      Serial.println("Publish OK");
      Serial.println(payload);
    } else {
      Serial.println("Publish Failed");
    }
  }
}