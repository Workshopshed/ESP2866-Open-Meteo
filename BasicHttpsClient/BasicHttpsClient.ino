/**
   open-meteo get the weather for Glasgow
   Using NodeMcu V2.1 chip CH9102X ESP-12F Development Board Module

   Based on the "BasicHttpsClient" example from https://arduino-esp8266.readthedocs.io/en/3.0.2/esp8266wifi/readme.html
*/

#include <Arduino.h>
#include "secret.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>
// Fingerprint for demo URL, Friday, 20 January 2023 at 18:47:00
// Get a new one by copying the SHA1 certificate for api.open-meteo.com
const uint8_t fingerprint[20] = {0x1e, 0x35, 0x2f, 0xc7, 0x25, 0x86, 0xad, 0xef, 0x96, 0x21, 0x55, 0xe0, 0x7c, 0x09, 0x66, 0x79, 0x70, 0xde, 0x85, 0xc3};

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SECRET_SSID, SECRET_PASS);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(fingerprint);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    //client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&current_weather=true")) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        String payload = https.getString();
        Serial.println(payload);
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}
