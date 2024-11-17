#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Spotify.h"
#include <LiquidCrystal_I2C.h>

// WiFi Credentials
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address, columns, rows
const int buttonPin = 17; // GPIO pin for the button

// Button state setup
bool buttonPressed = false;
bool buttonPressed_old = false;

// Spotify API
const char* access_token = "PASTE_ACCESS_TOKEN_HERE";

void setup() {
  // Initialize serial monitor
  Serial.begin(115200);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  lcd.setCursor(0, 1);
  lcd.print("WiFi Connected!");
  delay(2000);
  pinMode(buttonPin, INPUT_PULLUP);
  delay(100); // Allow time for the button pin state to stabilize
  buttonPressed = digitalRead(buttonPin); // Initialize with stable state
  buttonPressed_old = buttonPressed;
}

void scrollText(String text, String otherText, int row) {
  // If text length <= 16, scroll the line
  if (text.length() <= 16) {
    lcd.setCursor(0, row);
    lcd.print(text);
    lcd.setCursor(0, 1);
    lcd.print(otherText.substring(0, 16));
    buttonPressed = digitalRead(buttonPin);
    return;
  }
  // Scroll text
  for (int i = 0; i < text.length() - 16 + 1; i++) {
    lcd.setCursor(0, row);
    lcd.print(text.substring(i, i + 16));
    lcd.setCursor(0, 1);
    lcd.print(otherText.substring(0, 16));
    buttonPressed = digitalRead(buttonPin);
    delay(200);
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    String request = getCurrentPlay(access_token);
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, request);

    // Parse data needed
    const char* trackName = doc["item"]["name"];
    const char* trackId = doc["item"]["id"];
    const char* artistName = doc["item"]["artists"][0]["name"];
    bool isPlaying = doc["is_playing"];
    int progressMs = doc["progress_ms"];
    int durationMs = doc["item"]["duration_ms"];

    // Convert milliseconds to minutes:seconds
    int progressMinutes = (progressMs / 1000) / 60, progressSeconds = (progressMs / 1000) % 60;
    int durationMinutes = (durationMs / 1000) / 60, durationSeconds = (durationMs / 1000) % 60;

    // Prepare display strings
    String line1 = String(artistName) + " - " + String(trackName);
    String line2 = (isPlaying ? "|| " : "> ") +
                   String(progressMinutes) + ":" + (progressSeconds < 10 ? "0" : "") + String(progressSeconds) +
                   " / " +
                   String(durationMinutes) + ":" + (durationSeconds < 10 ? "0" : "") + String(durationSeconds);

    lcd.clear();
    scrollText(line1, line2, 0); // Scroll long text on the first line

    if (buttonPressed == 1 && buttonPressed_old == 0) {
      Serial.println("button pressed");
      lcd.setCursor(0, 1);
      Serial.println("Adding to Liked...");

      // Add track to playlist
      int add = addTrackToLiked(access_token, trackId);
      delay(200);
      lcd.setCursor(0, 1);
      lcd.print("Added!          ");
    }
    buttonPressed_old = buttonPressed;
  }
  delay(1);
}
