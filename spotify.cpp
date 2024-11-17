#include "spotify.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <base64.h>
#include <ArduinoJson.h>

String getCurrentPlay(String accessToken) {
  const char* apiUrl = "https://api.spotify.com/v1/me/player/currently-playing";
  HTTPClient http;
  http.begin(apiUrl);
  http.addHeader("Authorization", String("Bearer ") + accessToken);
  String err = "error";
  int httpResponseCode = http.GET();
  DynamicJsonDocument doc(1024);
  if (httpResponseCode == 200) {
    String payload = http.getString();
    Serial.println("getCurrentPlay : " + String(httpResponseCode));
    return payload;
  } else {
    Serial.println("Error fetching data:");
    Serial.println(httpResponseCode);
    return err;
  }
  http.end();
}

int addTrackToLiked(String accessToken, const char* trackId) {
  String url = "https://api.spotify.com/v1/me/tracks?ids="+String(trackId);
  HTTPClient http;
  http.begin(url);
  String auth = "Bearer " + String(accessToken);
  http.addHeader("Authorization",auth);
  http.addHeader("Content-Type","application/json");
  char requestBody[] = "{\"ids\":[\"string\"]}";
  int httpResponseCode = http.PUT(requestBody);
  bool success = false;

  // Check if the request was successful
  if (httpResponseCode == 200) {
    Serial.println("added track to liked songs");
    success = true;
  } 
  else {
    Serial.print("Error adding to liked songs: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  }
  http.end();
  return success;
}
