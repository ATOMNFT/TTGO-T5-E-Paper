#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

const char* ssid = "YOURSSID";
const char* password = "YOURPASSWORD";
const char* server_url = "http://YOURIPADDRESS:5000/stats";

#define EPD_CS 5
#define EPD_DC 17
#define EPD_RSET 16
#define EPD_BUSY 4

GxEPD2_BW<GxEPD2_290_GDEY029T94, GxEPD2_290_GDEY029T94::HEIGHT> display(GxEPD2_290_GDEY029T94(EPD_CS, EPD_DC, EPD_RSET, EPD_BUSY));

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    display.init();
    display.setRotation(1);
    display.setTextColor(GxEPD_BLACK);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(server_url);
        int httpResponseCode = http.GET();
        
        if (httpResponseCode > 0) {
            String payload = http.getString();
            Serial.println(payload);
            
            StaticJsonDocument<500> doc;
            deserializeJson(doc, payload);
            
            float cpu = doc["cpu"];
            float memory = doc["memory"];
            float disk = doc["disk"];
            String uptime = doc["uptime"];
            String cpu_temp = doc["cpu_temp"];

            display.firstPage();
            do {
                display.fillScreen(GxEPD_WHITE);
                display.setCursor(10, 18);
                display.setFont(&FreeMonoBold9pt7b);
                display.print("M-Base Stats");
                
                display.setCursor(10, 38);
                display.printf("CPU: %.1f%%", cpu);
                display.setCursor(10, 60);
                display.printf("Mem: %.1f%%", memory);
                display.setCursor(10, 80);
                display.printf("Disk: %.1f%%", disk);
                display.setCursor(10, 100);
                display.printf("Uptime: %s", uptime.c_str());
                display.setCursor(10, 120);
                display.printf("CPU Temp: %s", cpu_temp.c_str());
            } while (display.nextPage());
        }
        http.end();
    }
    delay(5000);
}
