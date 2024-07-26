#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Inisialisasi objek LCD dengan alamat I2C dan ukuran 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Konfigurasi pin untuk sensor suhu DS18B20
const int oneWireBus = 13;  // Pin GPIO untuk sensor suhu

// Inisialisasi OneWire dan DallasTemperature
OneWire oneWire(oneWireBus);
DallasTemperature sensor(&oneWire);

// Pin untuk relay
const int relayPin = 18;  // Pin GPIO untuk relay

// Pin untuk sensor kelembaban
#define sensorPin  26  // Pin GPIO untuk sensor kelembaban

void setup() {
  // Inisialisasi komunikasi serial
  Serial.begin(9600);

  

  // Inisialisasi LCD
  Wire.begin(21, 22); // Atur pin SDA dan SCL untuk LCD I2C
  lcd.init();
  lcd.backlight(); // Nyalakan backlight LCD
  lcd.setCursor(0, 0);
  lcd.print("Suhu Air:");

  // Inisialisasi pin relay sebagai output
  pinMode(relayPin, OUTPUT);

  // Inisialisasi sensor suhu DS18B20
  sensor.begin();
  pinMode(oneWireBus, INPUT);

  // Inisialisasi pin sensor kelembaban sebagai input
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Mendapatkan suhu dari sensor DS18B20
  sensor.requestTemperatures();
  float temperatureC = sensor.getTempCByIndex(0);

  // Periksa apakah suhu valid
  if (temperatureC == -127.0) {
    Serial.println("Gagal membaca suhu");
    return;
  }

  // Tampilkan suhu di Serial Monitor
  Serial.print("Suhu Air: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // Tampilkan suhu di LCD
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print(" C");

  // Kontrol relay berdasarkan suhu
  if (temperatureC >= 25.0) {
    digitalWrite(relayPin, HIGH); // Aktifkan relay jika suhu >= 25°C
    Serial.println("Relay ON");
  } else {
    digitalWrite(relayPin, LOW); // Matikan relay jika suhu < 25°C
    Serial.println("Relay OFF");
  }

  // Tunda 1 detik sebelum membaca suhu lagi
  delay(1000);
}