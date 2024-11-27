
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

const int UVPin = A0;  // Pin analógico donde está conectado el ML8511

void setup() {
  Serial.begin(9600);  // Comunicación serial con el ESP8266
  Wire.begin();  // Inicia I2C

  if (!bme.begin(0x76)) {
    Serial.println("No se encontró un sensor BME280 válido, verifica la conexión!");
    while (1);
  }
}

void loop() {
  // Leer datos del sensor BME280
  float temperature = bme.readTemperature();  // Temperatura en grados Celsius
  float humidity = bme.readHumidity();  // Humedad relativa en porcentaje (%)
  float pressure = bme.readPressure() / 100.0F;  // Presión atmosférica en hectopascales (hPa)

  // Leer datos del sensor ML8511
  int UVLevel = analogRead(UVPin);  // Nivel UV crudo del sensor (valor analógico entre 0 y 1023)

  // Incrementar la sensibilidad de la intensidad UV
  float UVIntensity = UVLevel * (15.0 / 1023.0);  // Ajuste de sensibilidad, escala completa de 0 a 15

  // Ajustar los valores a 2 cifras decimales
  temperature = round(temperature * 100.0) / 100.0;
  humidity = round(humidity * 100.0) / 100.0;
  pressure = round(pressure * 10.0) / 10.0;  // Presión con una cifra decimal
  UVIntensity = round(UVIntensity * 100.0) / 100.0;  // Intensidad UV con 2 cifras decimales

  // Enviar datos al ESP8266 en el formato: temperature,humidity,pressure,UVIntensity
  Serial.print(temperature);  // Valor 1: Temperatura
  Serial.print(",");
  Serial.print(humidity);  // Valor 2: Humedad
  Serial.print(",");
  Serial.print(pressure);  // Valor 3: Presión atmosférica
  Serial.print(",");
  Serial.println(UVIntensity);  // Valor 4: Intensidad UV

  delay(2000);  // Espera 2 segundos antes de la siguiente lectura
}
