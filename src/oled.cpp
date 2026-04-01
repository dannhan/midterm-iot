#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

// --- Pin Definitions untuk OLED SSD1331 ---
#define sclk 18  // SCL / SCK
#define mosi 23  // SDA / MOSI
#define cs   5   // CS (Chip Select)
#define rst  4   // RES (Reset)
#define dc   16  // DC (Data/Command)

// --- Pin Definitions untuk Sensor Ultrasonik HC-SR04 ---
#define TRIG_PIN 12
#define ECHO_PIN 14

// --- Definisi Warna (Format RGB565) ---
#define BLACK   0x0000
#define WHITE   0xFFFF
#define GREEN   0x07E0
#define YELLOW  0xFFE0
#define RED     0xF800

// Inisialisasi display
Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

// --- Konfigurasi Ukuran Tandon (dalam cm) ---
// Sesuaikan dengan tinggi maksimal wadah air Anda (dari dasar ke posisi sensor)
const int TINGGI_TANDON = 100; 

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi pin Ultrasonik
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Memulai display OLED
  display.begin();
  display.fillScreen(BLACK); 
  
  Serial.println("Sistem Peringatan Air Ultrasonik Dimulai");
}

void loop() {
  // 1. Proses memancarkan gelombang ultrasonik
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // 2. Membaca durasi pantulan gelombang
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // 3. Menghitung jarak (Kecepatan suara: 0.0343 cm/mikrodetik)
  int jarakSensorKeAir = duration * 0.034 / 2;
  
  // 4. Menghitung Ketinggian Air yang sebenarnya
  int waterLevel = TINGGI_TANDON - jarakSensorKeAir;
  
  // Mencegah nilai minus jika jarak sensor lebih besar dari tinggi tandon
  if (waterLevel < 0) {
    waterLevel = 0;
  }

  // 5. Tampilkan Teks Ketinggian Air
  // Menggunakan background BLACK pada setTextColor agar layar tidak perlu di-fillScreen 
  // (mencegah layar berkedip/flickering)
  display.setCursor(10, 10);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK); 
  display.print("Level Air: ");
  display.print(waterLevel);
  display.print(" cm   "); // Spasi ekstra untuk menimpa sisa angka sebelumnya

  // 6. Logika Peringatan (Warning)
  display.setCursor(10, 35);
  display.setTextSize(2);

  if (waterLevel < 30) {
    // Ketinggian < 30 cm -> AMAN (HIJAU)
    display.setTextColor(GREEN, BLACK);
    display.print("AMAN   "); 
    
  } else if (waterLevel >= 30 && waterLevel < 70) {
    // Ketinggian 30 - 69 cm -> WASPADA (KUNING)
    display.setTextColor(YELLOW, BLACK);
    display.print("WASPADA");
    
  } else {
    // Ketinggian >= 70 cm -> BAHAYA (MERAH)
    display.setTextColor(RED, BLACK);
    display.print("BAHAYA!");
  }

  // Jeda 1 detik sebelum pengukuran selanjutnya
  delay(1000); 
}