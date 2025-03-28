#include <WiFi.h>
#include <HTTPClient.h>

// ====== Wi-Fi credentials ======
const char* ssid = "Mesh_Floor";
const char* password = "thaochi0299";

// ====== Your IFTTT Webhook Key ======
const String IFTTT_KEY = "cgn2DIi4EtyRl6Y78v7vFZ";

// ====== Light sensor settings ======
const int lightSensorPin = 34;   // Use analog pin (e.g., GPIO 34)
const int threshold = 500;       // Adjust based on your testing
bool isSunlight = false;         // Track current state

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected.");
}

void loop() {
  int lightLevel = analogRead(lightSensorPin);
  Serial.print("Light level: ");
  Serial.println(lightLevel);

  // Detect sunlight start
  if (lightLevel > threshold && !isSunlight) {
    isSunlight = true;
    triggerIFTTT("sunlight_on");
  }
  // Detect sunlight stop
  else if (lightLevel <= threshold && isSunlight) {
    isSunlight = false;
    triggerIFTTT("sunlight_off");
  }

  delay(10000); // Check every 10 seconds
}

void triggerIFTTT(String eventName) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "http://maker.ifttt.com/trigger/" + eventName + "/with/key/" + IFTTT_KEY;
    http.begin(url);
    
    int httpCode = http.GET(); // Send HTTP GET request

    if (httpCode > 0) {
      Serial.println("IFTTT request sent: " + eventName);
    } else {
      Serial.println("Error sending request: " + http.errorToString(httpCode));
    }

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}
