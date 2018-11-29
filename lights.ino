
void shimmer() {

  for (int i = 0; i < PixelCount; i++) {

    RgbColor currentPixelColor = strip.GetPixelColor(i);

    strip.SetPixelColor(i+1, RgbColor(currentPixelColor.R/3,currentPixelColor.G/3,currentPixelColor.B/3));
    strip.SetPixelColor(i, RgbColor(currentPixelColor.R/2,currentPixelColor.G/2,currentPixelColor.B/2));
    strip.SetPixelColor(i-1, RgbColor(currentPixelColor.R/3,currentPixelColor.G/3,currentPixelColor.B/3));
    
    delay(100);
     strip.Show();
  }

  Serial.println("Shimmered");

}


void onEffects() {

  for (int i = 0; i < 10; i++) {

    int x = random(0,120);
    
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

}




