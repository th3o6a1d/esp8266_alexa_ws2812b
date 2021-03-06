void setColor(int r, int g, int b) {
  if ((r == 0) && (g == 0) && (b == 0)) {
    strip.ClearTo(hslBlack);
    colorMode = false;
    prog(true);
  } else {
    RgbColor c(r, g, b);
    HslColor color(c);
    for (int i = 0; i < PixelCount; i++) {
      if (i % 3 == 0) {
        strip.SetPixelColor(i, color);
      } else {
        strip.SetPixelColor(i, hslBlack);
      }
    }
    colorMode = true;
  }
  strip.Show();
}

void onEffects() {

  for (int i = 0; i < 10; i++) {

    int x = random(0, PixelCount);

    strip.SetPixelColor(x, RgbColor(244, 238, 65));
    delay(20);
    strip.Show();
    strip.SetPixelColor(x, RgbColor(255, 250, 107));
    delay(20);
    strip.Show();
    strip.SetPixelColor(x, RgbColor(255, 251, 153));
    delay(20);
    strip.Show();
    strip.SetPixelColor(x, RgbColor(255, 252, 186));
    delay(20);
    strip.Show();
    strip.SetPixelColor(x, RgbColor(255, 252, 85));
    delay(20);
    strip.Show();
    strip.SetPixelColor(x, hslBlack);
    delay(20);
    strip.Show();

  }

  strip.ClearTo(hslBlack);
  strip.Show();
}


void offEffects() {

  for (int i = 0; i < PixelCount + 6; i++) {
    strip.SetPixelColor(i, RgbColor(244, 238, 65));
    strip.SetPixelColor(i - 1, RgbColor(255, 250, 107));
    strip.SetPixelColor(i - 2, RgbColor(255, 251, 153));
    strip.SetPixelColor(i - 3, RgbColor(255, 252, 186));
    strip.SetPixelColor(i - 4, RgbColor(255, 252, 85));
    strip.SetPixelColor(i - 5, hslBlack);
    strip.Show();
    delay(10);
  }

  strip.ClearTo(hslBlack);
  strip.Show();

}





