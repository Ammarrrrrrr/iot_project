#define BLYNK_TEMPLATE_ID "TMPL2xlrVsJGb"
#define BLYNK_TEMPLATE_NAME "lightBar"
#define BLYNK_AUTH_TOKEN "pGMz3pfL8Rq4NkxkQrB12C3jTskdalnU"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT22
//#define POTPIN A0
//#define AirQuality A1  
DHT dht(DHTPIN, DHTTYPE);

char auth[] = BLYNK_AUTH_TOKEN;

// Replace with your Wi-Fi credentials
const char* ssid = "ssid";
const char* password = "password";

void setup() {
  // Debug console
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  dht.begin();

  Blynk.begin(auth, ssid, password);
  Serial.println("Blynk started");
}

void loop() {
  Blynk.run();

  // Read sensor values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
 // float noiseLevel = analogRead(POTPIN);
  //float airQuality = analogRead(AirQuality);

  // Check if readings are valid
  if (!isnan(temperature)) {
    Blynk.virtualWrite(V1, temperature); 
  } else {
    Serial.println("Failed to read temperature from DHT sensor");
  }

  if (!isnan(humidity)) {
    Blynk.virtualWrite(V2, humidity); 
  } else {
    Serial.println("Failed to read humidity from DHT sensor");
  }
  
  //Blynk.virtualWrite(V3, noiseLevel); 
  
  //Blynk.virtualWrite(V4, airQuality);

  delay(2000);
}
