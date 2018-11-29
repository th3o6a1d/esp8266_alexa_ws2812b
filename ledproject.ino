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

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);

// LEDs
int num_bikes_available = 0;
int num_ebikes_available = 0;
int num_bikes_disabled = 0;
bool expectRain = false;
float temperature = 0.0;
unsigned long lastExecuted = 0;

WiFiUDP UDP;
IPAddress ipMulti(239, 255, 255, 250);
ESP8266WebServer HTTP(80);
boolean udpConnected = false;
unsigned int portMulti = 1900;      // local port to listen on
unsigned int localPort = 1900;      // local port to listen on
boolean wifiConnected = false;
boolean relayState = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
String serial;
String persistent_uuid;
boolean cannotConnectToWifi = false;


void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  strip.Begin();
  strip.Show();

  initializeWiFi();
  prog();

}

void loop() {


  if ((millis() > lastExecuted + 60000) && (relayState)) {
    prog();
    lastExecuted = millis();
  }

  HTTP.handleClient();
  runServer();

}


