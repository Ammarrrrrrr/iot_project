#define BLYNK_TEMPLATE_ID "TMPL2xlrVsJGb"
#define BLYNK_TEMPLATE_NAME "lightBar"
#define BLYNK_AUTH_TOKEN "pGMz3pfL8Rq4NkxkQrB12C3jTskdalnU"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT22
#define LED_PIN 14

DHT dht(DHTPIN, DHTTYPE);

char auth[] = BLYNK_AUTH_TOKEN;

const char* ssid = "ammar";
const char* password = "00000000";

void setup() {
  // Debug console
  Serial.begin(9600);

  // Set LED pin as output
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  dht.begin();

  Blynk.begin(auth, ssid, password);
  Serial.println("Blynk started");

  // Initialize the random number generator
  randomSeed(analogRead(A0));
}

void loop() {
  Blynk.run();

  // Read sensor values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int noiseLevel = random(45, 75); // Simulated noise level (dB)
  int airQuality = random(20, 150);  // Simulated AQI range

  if (!isnan(temperature)) {
    Blynk.virtualWrite(V1, temperature); 
    if (temperature >= 24.00) {digitalWrite(LED_PIN, HIGH);Blynk.virtualWrite(V5,1);} else {digitalWrite(LED_PIN,LOW );Blynk.virtualWrite(V5,0);}
  } else {
    Serial.println("Failed to read temperature from DHT sensor");
  }

  if (!isnan(humidity)) {
    Blynk.virtualWrite(V2, humidity); 
  } else {
    Serial.println("Failed to read humidity from DHT sensor");
  }

  // Send realistic values to Blynk
  Blynk.virtualWrite(V3, noiseLevel); 
  Blynk.virtualWrite(V4, airQuality);

  delay(2000);
}
