#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define pixelCount 150


Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, PIN, NEO_GRB + NEO_KHZ800);
uint32_t original[pixelCount];

#define orange strip.Color(200, 50, 0)
#define pink strip.Color(150, 30, 30)
#define yellow strip.Color(120, 100, 0)
#define white strip.Color(90, 70, 80)
#define lime strip.Color(30, 60, 10)
#define blue strip.Color(0, 0, 150)
#define red strip.Color(150, 0, 0)
#define green strip.Color(0, 150, 0)
#define magenta strip.Color(150, 0, 120)
#define purple strip.Color(120, 0, 200)
#define off strip.Color(0,0,0)

void setup() {

  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(75);
  strip.show(); // Initialize all pixels to 'off'

  //  uint32_t a =  strip.Color(0, 0, 150);//
  //  uint32_t b = strip.Color(120, 100, 0);//red
  //  uint32_t c = strip.Color(255, 182, 108);//green
    uint32_t arry[] = {green,blue};
    linearPattern(arry,1);
    initOriginalColorArray();


}

void loop() {
  //colorWipe(green, 0, 150, 50);
  //theaterChase(blue, 100);
  //theaterChaseRainbow(50);
  //cyclePattern(5, 50);
  rainbowCycle(50);         //MAIN
  //trail(blue, 10, 50);    //LMAO IT BROKE
  //uint32_t ay[] = {green, blue};
  //colorWipeCycle(ay, 2, 50);
  strip.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t startPixel, uint16_t endPixel, uint8_t wait) {
  for (uint16_t i = startPixel; i < endPixel; i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void colorWipeCycle(uint32_t Colors[], uint8_t n, uint8_t wait){
  uint32_t c = 0;
  for(int j = 0; j < n; j++){
    c = Colors[j];
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
    if(j == n){
      j = 0;
      }
    }
  
  
  }

void cyclePattern(uint8_t cycles, uint8_t wait) {

  int x = 0;
  while (x < cycles) {
    for (uint16_t j = 0; j < strip.numPixels() + 1; j++) { //index in the original array
      for (uint16_t i = 0; i < strip.numPixels(); i++) { //index in the LEDs
        uint32_t c = 0;
        if (i + j > strip.numPixels() - 1) {
          c = original[i + j - strip.numPixels() + 1];
        } else {
          c = original[i + j];
        }
        strip.setPixelColor(i, c);
      }
      strip.show();
      delay(wait);
    }
    x++;
  }
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

void trail(uint32_t c, uint8_t tail, uint8_t wait) {
  int pixelDivision = tail;
  int b = 50;
  int change = floor(b / tail);
  for (uint16_t i = 0; i < pixelCount/pixelDivision; i++) {
     b -= change * i;
    for (uint16_t j = pixelDivision * i; j < pixelCount; j++) {
      strip.setPixelColor(j, c * b);
    }

  }
}

void initOriginalColorArray() {

  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    original[i] = strip.getPixelColor(i);
    //Serial.print("LED "); Serial.print(i); Serial.print(" is: "); Serial.println(original[i]);
  }

}

void linearPattern(uint32_t Colors[], int n) {
  int pixelDivision = floor(pixelCount / n);
  for (uint16_t i = 0; i < n; i++) {
    uint32_t c = Colors[i];
    for (uint16_t j = pixelDivision * i; j < pixelCount; j++) {
      strip.setPixelColor(j, c);
    }

  }
  if (pixelDivision * n < pixelCount) {
    for (int j = pixelDivision * n; j < pixelCount; j++) {
      strip.setPixelColor(j, Colors[0]);
    }
  }

}




// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
