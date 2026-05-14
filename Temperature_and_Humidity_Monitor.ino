#include <DHT.h>

// DHT11 connected to GPIO 4
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(115200);

  Serial.println("DHT11 Sensor with ESP32");

  dht.begin();

  delay(2000);   // Sensor startup delay
}

void loop() {

  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if sensor reading failed
  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("Failed to read from DHT11 sensor!");

  } else {

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.println("----------------------");

  delay(2000);
}
