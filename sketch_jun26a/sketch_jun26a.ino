#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

void setup() {
  Serial.begin(9600);

  Wire.begin(D2, D1); // Menginisialisasi komunikasi I2C dengan pin SDA (D2) dan SCL (D1)

  // Inisialisasi sensor MAX30102
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("Sensor tidak ditemukan. Periksa koneksi dan alamat I2C!");
    while (1);
  }

  // Konfigurasi sensor
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A); // Mengatur amplitudo LED merah
  particleSensor.setPulseAmplitudeIR(0x0A); // Mengatur amplitudo LED inframerah
  particleSensor.setSampleRate(100); // Mengatur kecepatan sampling menjadi 100 sps (sample per second)
  particleSensor.enableDIETEMPRDY();

  delay(1000);
}

void loop() {
  // Membaca data dari sensor
  if (particleSensor.available()) {
    int32_t irValue = particleSensor.getIR();
    int32_t redValue = particleSensor.getRed();
    int32_t tempValue = particleSensor.readTemperature();

    // Menampilkan data pada Serial Monitor
    Serial.print("IR: ");
    Serial.print(irValue);
    Serial.print(", Red: ");
    Serial.print(redValue);
    Serial.print(", Temperature: ");
    Serial.println(tempValue / 100.0); // Konversi suhu menjadi derajat Celsius

    // Delay antara pembacaan data
    delay(1000);
  }
}
