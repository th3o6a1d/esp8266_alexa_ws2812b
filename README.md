# ESP8266 Alexa WS2812B Project

## Goal

- Make a programmable LED strip that conveys useful information with a minimalist aesthetic by pining various APIs. Examples:

  - Continuously display number of citibikes available at my nearest station.

  - Display current temperature. 

- Turn it on/off with Alexa.

## Components

- [ESP8266 board](https://www.amazon.com/gp/product/B01IK9GEQG/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1)

- [LED Lights with WS8212B chipset](https://www.amazon.com/gp/product/B01CDTEFAQ/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1). Comes with a male/female JST connector on front end/backend.

- USB cord 

- JST connectors 

### Notes: 

- No additional power source required if number of lights is small ~100 or less. 

- Need a way of connecting ESP8266 to the lights. Recommend connecting a female JST connector w/ solder or pins. 

## Wiring

The LED lights have a signil wire (green), power (red), and ground (white). Connect ground to a GND on ESP8266 opposite side from connected red to a 3.3V input. 

## Code

- Rename `settings_example.h` to `settings.h` and include your WiFi credentials

I broke the sketch for this project into several .ino files. 
 
- `ledproject.ino` -- Global variables, setup(), loop()
- `api.ino` -- some WiFi API calls to update the global variables
- `lights.ino` -- to update the light display
- `networking.ino` -- makes the device discoverable by Alexa. Comes from: (https://github.com/kakopappa/arduino-esp8266-alexa-wemo-switch/blob/master/sinric.ino).