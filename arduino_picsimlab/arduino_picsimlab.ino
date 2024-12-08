#define BLYNK_TEMPLATE_ID "TMPL2xlrVsJGb"
#define BLYNK_TEMPLATE_NAME "lightBar"
#define BLYNK_AUTH_TOKEN "pGMz3pfL8Rq4NkxkQrB12C3jTskdalnU"

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <DHT.h>

#define W5100_CS  10
#define SDCARD_CS 4
#define DHTPIN 2       
#define DHTTYPE DHT11  
#define POTPIN A0      
#define AirQuality A1 
DHT dht(DHTPIN, DHTTYPE);



char auth[] = BLYNK_AUTH_TOKEN;

void setup() {
  // Debug console
  Serial.begin(9600);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card

  dht.begin();

  Blynk.begin(auth);
  Serial.println("Blynk started");
}

void loop() {
  Blynk.run();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float noiseLevel = analogRead(POTPIN);
  float AirQuality = analogRead(AirQuality);

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
  
  Blynk.virtualWrite(V3, noiseLevel); 
  
  Blynk.virtualWrite(V4, AirQuality); 

  delay(2000); 
}
