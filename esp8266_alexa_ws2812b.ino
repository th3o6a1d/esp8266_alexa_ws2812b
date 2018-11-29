#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <NeoPixelBus.h>
#include <functional>
#include "settings.h"

#define colorSaturation 1
const uint16_t PixelCount = 118;
const uint8_t PixelPin = 4;

NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);
RgbColor yellow(115, 119, 39);
RgbColor orange(244, 191, 66);

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslYellow(yellow);
HslColor hslOrange(orange);
HslColor hslBlack(black);

// Bikes
int bikesLastUpdated = 0;
const int bikesStart = 10;
const int bikesFinish = 61;
int numBikesAvailable = 0;
int numEBikesAvailable = 0;
int numBikesDisabled = 0;

// Temperature
const int tempStart = 80;
const int tempFinish = 90;
float temperature = 0.0;
int weatherLastUpdated = 0;

WiFiUDP UDP;
IPAddress ipMulti(239, 255, 255, 250);
ESP8266WebServer HTTP(80);
boolean udpConnected = false;
unsigned int portMulti = 1900;      
unsigned int localPort = 1900;      
boolean wifiConnected = false;
boolean relayState = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; 
String serial;
String persistent_uuid;
boolean cannotConnectToWifi = false;

void prog(bool startOver) {

  if (((millis() > weatherLastUpdated + 300000) && (relayState)) || startOver) {
    updateWeather();
    weatherLastUpdated = millis();
  }

  if (((millis() > bikesLastUpdated + 60000) && (relayState)) || startOver){
    updateBikes();
    bikesLastUpdated = millis();
  }
  
}


void setup() {
  Serial.begin(115200);
  strip.Begin();
  strip.Show();
  startNetworking();
  prog(true);
}

void loop() {
  prog(false);
  HTTP.handleClient();
  runServer();
}




