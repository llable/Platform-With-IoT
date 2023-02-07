#include <WiFi.h>

const char* ssid     = "Your-Wifi-Name";
const char* password = "Your-Wifi-Password";

void setup()
{
    // Baud sync with a serial monitor
    Serial.begin(115200);
    delay(10);

    Serial.println();
    Serial.print("[ESP32] Connecting to ");
    Serial.println(ssid);

    // The mode for ESP32 connects to an access point(wifi).
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // To set auto connect off, use the following function
    // WiFi.setAutoReconnect(false);

    // Will try for about 10 seconds (1 sec X 10 times)
    int tryDelay = 1000;
    int numOfTries = 10;

    // Wait for the WiFi event
    while (true) {
        switch(WiFi.status()) {
          case 1:
            Serial.println("[ESP32] SSID not found");
            break;
          case 3:
            Serial.println("[ESP32] WiFi is connected!");
            Serial.print("[ESP32] IP address: ");
            Serial.println(WiFi.localIP());
            return;
            break;
          case 4:
            Serial.print("[ESP32] Failed - WiFi not connected! Reason: ");
            return;
            break;
          case 5:
            Serial.println("[ESP32] Connection was lost");
            break;
          case 6:
            if(numOfTries != 10){
              Serial.println("[ESP32] WiFi is disconnected");
            }
            break;
          default:
            Serial.print("[ESP32] WiFi Status: ");
            Serial.println(WiFi.status());
            break;
        }
        delay(tryDelay);
        
        if(numOfTries <= 0){
          Serial.print("[WiFi] Failed to connect to WiFi!");
          // Use disconnect function to force stop trying to connect
          WiFi.disconnect();
          return;
        } else {
          numOfTries--;
        }
    }
}

void loop()
{
}
