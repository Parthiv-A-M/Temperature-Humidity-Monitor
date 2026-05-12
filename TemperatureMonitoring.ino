#include <WiFi.h>
#include "DHT.h"
#include <ThingSpeak.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "Realme_8_Pro";
const char* password = "Parthiv@18";

unsigned long channelID = 3380670;
const char* apiKey = "CM998CEH0DZWPD8Y";

WiFiClient client;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  ThingSpeak.begin(client);
}

void loop() {

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C  ");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, hum);

  int x = ThingSpeak.writeFields(channelID, apiKey);

  if (x == 200) {
    Serial.println("Data sent to ThingSpeak");
  } else {
    Serial.println("Upload failed");
  }

  delay(15000);
}