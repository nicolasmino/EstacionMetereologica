#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Include libraries for RS485 communication
#include <SoftwareSerial.h>
SoftwareSerial RS485Serial(10, 11); // RX, TX

// Define BME280 sensor pins
#define BME_SDA A4
#define BME_SCL A5
#define BME_CS A6
#define BME_MISO A7

// Initialize BME280 sensor
Adafruit_BME280 bme;

// Define MQ135 sensor pin
#define MQ135_PIN A0

// Define ML8511 sensor pin
#define ML8511_PIN A3

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize RS485 serial communication
  RS485Serial.begin(9600);

  // Initialize I2C communication for BME280
  Wire.begin();
  bme.begin(BME_CS);

  // Set up ADC for MQ135 sensor
  pinMode(MQ135_PIN, INPUT);

  // Set up ADC for ML8511 sensor
  pinMode(ML8511_PIN, INPUT);
}

void loop() {
  // Read BME280 sensor data
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F; // Convert Pa to hPa

  // Read MQ135 sensor data (air quality)
  int airQuality = analogRead(MQ135_PIN);

  // Read ML8511 sensor data (UV intensity)
  int uvIntensity = analogRead(ML8511_PIN);

  // Print sensor data for debugging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
  Serial.print("Air Quality: ");
  Serial.println(airQuality);
  Serial.print("UV Intensity: ");
  Serial.println(uvIntensity);

  // Construct data packet for RS485 transmission
  String dataPacket = String(temperature) + "," + String(humidity) + "," + String(pressure) + "," + String(airQuality) + "," + String(uvIntensity);
  
  // Transmit data packet via RS485
  RS485Serial.println(dataPacket);

  delay(5000); // Adjust delay as needed for your application
}
