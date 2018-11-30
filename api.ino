


void updateBikes() {

  strip.SetPixelColor(bikesStart - 3, hslYellow);

  // Display the broken bikes
  for (int i = bikesStart; i < bikesFinish; i ++) {
    if (i < bikesStart + numBikesDisabled) {
      strip.SetPixelColor(i, hslRed);
    } else {
      strip.SetPixelColor(i, hslBlack);
    }
  }

  // Display the current number of available bikes
  for (int i = bikesStart + numBikesDisabled; i < bikesFinish; i ++) {
    if (i < bikesStart + numBikesDisabled + numBikesAvailable) {
      strip.SetPixelColor(i, hslGreen);
    } else {
      strip.SetPixelColor(i, hslBlack);
    }
  }

  // Display the current number of EBikes available
  for (int i = bikesStart + numBikesDisabled + numBikesAvailable; i < bikesFinish; i ++) {
    if (i < bikesStart + numBikesDisabled + numBikesAvailable + numEBikesAvailable) {
      strip.SetPixelColor(i, hslYellow);
    } else {
      strip.SetPixelColor(i, hslBlack);
    }
  }
  strip.Show();

  const char* host = "gbfs.citibikenyc.com";
  const String url = "/gbfs/en/station_status.json";
  const uint16_t port = 80;

  WiFiClient client;
  client.connect(host, port);
  client.print("GET " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Connection: keep-alive\r\n\r\n");
  client.println();

  String preJSON = "";
  while (client.connected()) {
    preJSON = client.readStringUntil('}');
    if (preJSON.indexOf("\"station_id\":\"422\"") > 0) {
      preJSON.remove(0, 1);
      preJSON = preJSON + "}";
      break;
    }
  }
  client.stop();

  const size_t bufferSize = JSON_OBJECT_SIZE(11) + 250;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.parseObject(preJSON);
  const char* station_id = root["station_id"];

  // Calculate number of changed bikes
  int bikeChange = sqrt(sq((int) root["num_bikes_available"] + (int) root["num_ebikes_available"] + (int) root["num_bikes_disabled"] - numBikesAvailable - numEBikesAvailable - numBikesDisabled));

  // Blink just that number of bikes
  for (int x = 0; x < 3; x++) {
    for (int i = bikesStart; i < bikesStart + bikeChange; i++) {
      strip.SetPixelColor(i, hslBlue);
    }
    strip.Show();
    delay(1000);
    for (int i = bikesStart; i < bikesStart + bikeChange; i++) {
      strip.SetPixelColor(i, hslBlack);
    }
    strip.Show();
    delay(1000);
  }

  numBikesDisabled = root["num_bikes_disabled"];
  numBikesAvailable = root["num_bikes_available"];
  numEBikesAvailable = root["num_ebikes_available"];

  Serial.println("Bike change: " + String(bikeChange));
  Serial.println("Disabled bikes: " + String(numBikesDisabled));
  Serial.println("Available bikes: " + String(numBikesAvailable));
  Serial.println("Available ebikes: " + String(numEBikesAvailable));

  // Display the broken bikes
  for (int i = bikesStart; i < bikesFinish; i ++) {
    if (i < bikesStart + numBikesDisabled) {
      strip.SetPixelColor(i, hslRed);
    } else {
      strip.SetPixelColor(i, hslBlack);
    }
  }

  // Display the current number of available bikes
  for (int i = bikesStart + numBikesDisabled; i < bikesFinish; i ++) {
    if (i < bikesStart + numBikesDisabled + numBikesAvailable) {
      strip.SetPixelColor(i, hslGreen);
    } else {
      strip.SetPixelColor(i, hslBlack);
    }
  }

  // Display the current number of EBikes available
  for (int i = bikesStart + numBikesDisabled + numBikesAvailable; i < bikesFinish; i ++) {
    if (i < bikesStart + numBikesDisabled + numBikesAvailable + numEBikesAvailable) {
      strip.SetPixelColor(i, hslYellow);
    } else {
      strip.SetPixelColor(i, hslBlack);
    }
  }

  strip.SetPixelColor(bikesStart - 3, hslBlack);
  strip.Show();
}


void updateWeather() {

  strip.SetPixelColor(tempStart + 13, hslYellow);
  // Update LEDs
  int tTotal = round(tempFinish - temperature / 10);
  for (int n = tempStart; n < tTotal; n ++) {
    strip.SetPixelColor(n, hslBlue);
  }
  for (int i = tTotal; i < tempFinish; i++) {
    strip.SetPixelColor(i, hslRed);
  }
  strip.Show();
  
  String url = "/data/2.5/forecast?q=New%20York&" + openWeatherAppId + "&mode=json&units=metric";
  WiFiClient client;
  client.connect("api.openweathermap.org", 80);
  client.print("GET " + url + " HTTP/1.0\r\n"
               "Content-Type: application/json\r\n" +
               "Connection: keep-alive\r\n\r\n");
  client.println();

  while (client.connected()) {
    String line = client.readStringUntil(',');
    if (line.indexOf("main\":{\"temp") >= 0) {
      String t = line.substring(line.length(), line.length() - 4);
      temperature = t.toFloat() * (9 / 5) + 32;
      break;
    }
    if(line == ""){
      break;
    }
  }
  client.stop();

  // Update LEDs
  tTotal = round(tempFinish - temperature / 10);
  for (int n = tempStart; n < tTotal; n ++) {
    strip.SetPixelColor(n, hslBlue);
  }
  for (int i = tTotal; i < tempFinish; i++) {
    strip.SetPixelColor(i, hslRed);
  }

  strip.SetPixelColor(tempStart + 13, hslBlack);
  strip.Show();
}







