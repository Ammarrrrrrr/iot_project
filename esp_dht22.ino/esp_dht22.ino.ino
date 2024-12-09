#define BLYNK_TEMPLATE_ID "TMPL2xlrVsJGb"
#define BLYNK_TEMPLATE_NAME "lightBar"
#define BLYNK_AUTH_TOKEN "pGMz3pfL8Rq4NkxkQrB12C3jTskdalnU"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT22
#define LED_PIN 

DHT dht(DHTPIN, DHTTYPE);

char auth[] = BLYNK_AUTH_TOKEN;

const char* ssid = "WEHOME11";
const char* password = "4080740807";

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
  // Generate random values for noise level and air quality
  int noiseLevel = random(30, 100); // Simulated noise level (dB)
  int airQuality = random(0, 500);  // Simulated air quality index (AQI)

  if (!isnan(temperature)) {
    Blynk.virtualWrite(V1, temperature); 
    if (temperature > 24.00) {digitalWrite(LED_PIN, HIGH);} else {digitalWrite(LED_PIN,LOW );}
  } else {
    Serial.println("Failed to read temperature from DHT sensor");
  }

  if (!isnan(humidity)) {
    Blynk.virtualWrite(V2, humidity); 
  } else {
    Serial.println("Failed to read humidity from DHT sensor");
  }

  // Send random values to Blynk
  Blynk.virtualWrite(V3, noiseLevel); 
  Blynk.virtualWrite(V4, airQuality);

  delay(2000);
}
