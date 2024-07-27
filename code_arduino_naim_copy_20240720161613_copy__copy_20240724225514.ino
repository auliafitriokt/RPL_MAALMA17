#include <Wire.h>                   // Library untuk komunikasi I2C
#include <LiquidCrystal_I2C.h>      // Library untuk LCD I2C

#define SENSOR_PIN 34               // Pin ADC yang digunakan untuk sensor kelembapan tanah
#define RELAY_PIN 23                // Pin digital yang digunakan untuk relay
#define THRESHOLD 3000              // Nilai ambang batas untuk menentukan tanah kering (sesuaikan jika perlu)

// Inisialisasi LCD dengan alamat I2C (0x27 atau 0x3F, tergantung modul Anda) dan ukuran layar
LiquidCrystal_I2C lcd(0x27, 16, 2); // Ganti 0x27 dengan alamat I2C dari LCD Anda jika berbeda

void setup() {
  Serial.begin(115200);            // Mulai komunikasi serial
  lcd.init();                      // Inisialisasi LCD
  lcd.backlight();                // Nyalakan lampu latar LCD
  lcd.setCursor(0, 0);            // Set posisi kursor ke baris pertama
  lcd.print("Soil Moisture:");    // Tampilkan pesan awal
  
  pinMode(RELAY_PIN, OUTPUT);     // Set pin relay sebagai output
  digitalWrite(RELAY_PIN, LOW);   // Pastikan relay mati saat startup
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);   // Baca nilai dari sensor
  Serial.print("Raw Sensor Value: ");
  Serial.println(sensorValue);

  // Update LCD dengan nilai sensor dan status relay
  lcd.setCursor(0, 1);  // Set posisi kursor ke baris kedua
  lcd.print("Value: ");
  lcd.print(sensorValue);
  lcd.print("  "); // Tambahkan spasi untuk menghapus nilai lama

  // Aktifkan relay jika tanah kering (nilai sensor > ambang batas)
  if (sensorValue > THRESHOLD) {
    digitalWrite(RELAY_PIN, LOW);   // Matikan relay (perbaiki logika jika relay aktif LOW)
    lcd.setCursor(0, 0); // Pindahkan kursor ke baris pertama
    lcd.print("Relay: OFF  "); // Tampilkan status relay
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Nyalakan relay (perbaiki logika jika relay aktif HIGH)
    lcd.setCursor(0, 0); // Pindahkan kursor ke baris pertama
    lcd.print("Relay: ON   "); // Tampilkan status relay
  }

  delay(1000);  // Tunggu 1 detik sebelum membaca lagi
}
