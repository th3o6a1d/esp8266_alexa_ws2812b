

void prog() {
  updateBikes();
  Serial.println("Did bikes");
  rainToday();
  Serial.println("Got weather");
  blinkLights();
  Serial.println("Updated lights");
  strip.Show();
}


void blinkLights() {

  // Bikes
  for (int ledIndex = 0; ledIndex < PixelCount; ledIndex ++) {
    if ((ledIndex < num_bikes_available) && (ledIndex < 20)) {
      strip.SetPixelColor(ledIndex, hslGreen);
    } else {
      strip.SetPixelColor(ledIndex, hslBlack);
    }
  }

//  // Umbrella
//  if (expectRain) {
//    strip.SetPixelColor(111, hslBlue);
//  } else {
//    strip.SetPixelColor(111, hslWhite);
//  }

  // Temp
  int tTotal = round(91 - temperature / 10);
  for (int n = 80; n < tTotal; n ++) {
    strip.SetPixelColor(n, hslBlue);
  }
  for (int ledIndex = tTotal; ledIndex < 91; ledIndex++) {
    strip.SetPixelColor(ledIndex, hslRed);
  }

}


