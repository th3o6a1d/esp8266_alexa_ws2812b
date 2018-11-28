


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
  const size_t bufferSize = JSON_OBJECT_SIZE(11) + 250;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.parseObject(preJSON);
  const char* station_id = root["station_id"];
  num_bikes_available = root["num_bikes_available"];
  num_ebikes_available = root["num_ebikes_available"];
  num_bikes_disabled = root["num_bikes_disabled"];
  client.stop();
}


void rainToday() {
  String url = "/data/2.5/forecast?q=New%20York&APPID=650e8d6761fa2927fb04ecaad3b6d7ef&mode=json&units=metric";
  WiFiClient client;
  client.connect("api.openweathermap.org", 80);
  client.print("GET " + url + " HTTP/1.0\r\n"
               "Content-Type: application/json\r\n" +
               "Connection: keep-alive\r\n\r\n");
  client.println();

  expectRain = false;
  temperature = 0;

  int counter = 0;
  while (client.connected()) {
    counter += 1;
    String line = client.readStringUntil(',');
    if ((line.indexOf('temp') > 0) && (temperature == 0)) {
      String t = line.substring(line.indexOf('temp') + 6, line.indexOf('temp') + 10);
      temperature = t.toInt() * (9 / 5) + 32;
    }

    String weatherCode = "\"weather\":[{\"id\":";

    Serial.println(line.substring(line.indexOf(weatherCode), line.indexOf(weatherCode) + 18));
    if ((line.indexOf(weatherCode) > 0) && (line.substring(line.indexOf(weatherCode) + 18) == "5")) {
      Serial.println(line);
      expectRain = true;
      Serial.println(expectRain);
    }
    if (line == "") {
      break;
    }
  }

  client.stop();
}





