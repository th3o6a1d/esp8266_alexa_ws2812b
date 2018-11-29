


void updateBikes() {

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

  int bikeChange = sqrt(sq((int) root["num_bikes_available"] - numBikesAvailable));

  numBikesDisabled = root["num_bikes_disabled"];

  for (int i = bikesStart; i < bikesFinish; i ++) {
    if (i < bikesStart + numBikesDisabled) {
      strip.SetPixelColor(i, hslRed);
    } else {
      strip.SetPixelColor(i, hslBlack);
    }
  }

  for (int x = 0; x < 3; x++) {
    for (int i = bikesStart + numBikesDisabled + numBikesAvailable; i < bikesStart + numBikesDisabled + numBikesAvailable + bikeChange; i++) {
      strip.SetPixelColor(i, hslGreen);
    }
    strip.Show();
    delay(1000);
    for (int i = bikesStart + numBikesDisabled + numBikesAvailable; i < bikesStart + numBikesDisabled + numBikesAvailable + bikeChange; i++) {
      strip.SetPixelColor(i, hslBlack);
    }
    strip.Show();
    delay(1000);
  }

  numBikesAvailable = root["num_bikes_available"];
  numEBikesAvailable = root["num_ebikes_available"];
  
  strip.Show();

  for (int i = bikesStart + numBikesDisabled; i < bikesFinish; i ++) {
    if (i < bikesStart + numBikesDisabled + numBikesAvailable) {
      strip.SetPixelColor(i, hslGreen);
    } else {
      strip.SetPixelColor(i, hslBlack);
    }
  }
  for (int i = bikesStart + numBikesAvailable; i < bikesFinish; i ++) {
    if (i < bikesStart + numBikesAvailable + numEBikesAvailable) {
      strip.SetPixelColor(i, hslYellow);
    } else {
      strip.SetPixelColor(i, hslBlack);
    }
  }

  strip.Show();

}


void updateWeather() {
  String url = "/data/2.5/forecast?q=New%20York&APPID=650e8d6761fa2927fb04ecaad3b6d7ef&mode=json&units=metric";
  WiFiClient client;
  client.connect("api.openweathermap.org", 80);
  client.print("GET " + url + " HTTP/1.0\r\n"
               "Content-Type: application/json\r\n" +
               "Connection: keep-alive\r\n\r\n");
  client.println();

  temperature = 0;
  int counter = 0;
  while (client.connected()) {
    counter += 1;
    String line = client.readStringUntil(',');
    if ((line.indexOf('temp') > 0) && (temperature == 0)) {
      String t = line.substring(line.indexOf('temp') + 6, line.indexOf('temp') + 10);
      temperature = t.toInt() * (9 / 5) + 32;
    }

    if (line == "") {
      break;
    }
  }
  client.stop();

  // Update LEDs
  int tTotal = round(tempFinish - temperature / 10);
  for (int n = tempStart; n < tTotal; n ++) {
    strip.SetPixelColor(n, hslBlue);
  }
  for (int i = tTotal; i < tempFinish; i++) {
    strip.SetPixelColor(i, hslRed);
  }
  strip.Show();
}







