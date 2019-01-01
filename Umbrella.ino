// Include a library for LED strips:
#include <FastLED.h>
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define COLOR_ORDER GRB
#define LED_TYPE    WS2811 // Define a type of LED strips
// Define digital pins that LED strips are connected to:
#define DATA_PIN1    6
#define DATA_PIN2    7
#define DATA_PIN3    8
#define DATA_PIN4    9
// Define arrays for each LED strip"
CRGB leds1[37];
CRGB leds2[37];
CRGB leds3[37];
CRGB leds4[37];
int waterSensors[] = {A5, A4, A3, A2}; // define analog pins for water sensors
int lightCell = A1;  // define an analogue pin for a light sensor
int tempCell = A0;   // define an analogue pin for a temperature sensor

void setup() {
  Serial.begin(9600); // Set up a serial monitor for debugging
  // Set water sensors as INPUTs:
  for(int i=0; i<4; i++) {
    pinMode(waterSensors[i], INPUT);
  }
  pinMode(lightCell, INPUT);  // set photosensor as INPUT
  pinMode(tempCell, INPUT);   // set temperature sensor as INPUT
  
  FastLED.addLeds<LED_TYPE, DATA_PIN1, COLOR_ORDER>(leds1, 37).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(leds2, 37).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN3, COLOR_ORDER>(leds3, 37).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN4, COLOR_ORDER>(leds4, 37).setCorrection(TypicalLEDStrip);
  delay(3000); // 3 second delay for recovery
}

void loop() {
  // Read in a temperature value from a temperature sensor and convert it to Celcium:
  float temperature = analogRead(tempCell) * 0.004882814;
  temperature = (temperature - .5) *100;
  Serial.println(temperature);

  // Set the primary colour of LED strips as blue if the temperature falls below 10:
  if(temperature<=10) {
    int i = 0;
      while(i< 37){
        leds1[i] = CRGB(5,5,15);
        leds2[i] = CRGB(5,5,15);
        leds3[i] = CRGB(5,5,15);
        leds4[i] = CRGB(5,5,15);
        i++;
      }
  }
  // Set the primary colour of LED strips as red if the temperature raises above 10:
  else if(temperature>10) {
    int i = 0;
      while(i< 37){
        leds1[i] = CRGB(20,5,5);
        leds2[i] = CRGB(20,5,5);
        leds3[i] = CRGB(20,5,5);
        leds4[i] = CRGB(20,5,5);
        i++;
      }
  }

  // Turn on first LED strip if first water sensor is in water:
   if (digitalRead(waterSensors[0]) != 0) {
      fadeToBlackBy( leds1, 37, 20); // A built-in method for LED strips from the fastLED library
      byte dothue = 0;
      for( int i = 0; i < 8; i++) {
        leds1[beatsin16( i+7, 0, 37-1 )] |= CHSV(dothue, 200, 255);
        dothue += 32;
      }
    }
  // Turn off first LED strip if first water sensor is not in water:
   else if (digitalRead(waterSensors[0]) == 0) {
      int i = 0;
      while(i< 37){
        leds1[i] = CRGB::Black;
        i++;
      }
   }
  // Turn on second LED strip if second water sensor is in water:
  if (digitalRead(waterSensors[1]) != 0) {
    fadeToBlackBy( leds2, 37, 20);
    byte dothue = 0;
    for( int i = 0; i < 8; i++) {
      leds2[beatsin16( i+7, 0, 37-1 )] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
  }
  // Turn off second LED strip if second water sensor is not in water:
  else if (digitalRead(waterSensors[1]) == 0) {
     int j = 0;
    while(j< 37){
      leds2[j] = CRGB::Black;
      j++;
    }
   }
  // Turn on third LED strip if third water sensor is in water:
   if (digitalRead(waterSensors[2]) != 0) {
    fadeToBlackBy( leds3, 37, 20);
    byte dothue = 0;
    for( int i = 0; i < 8; i++) {
      leds3[beatsin16( i+7, 0, 37-1 )] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
  }
  // Turn off third LED strip if third water sensor is not in water:
  else if (digitalRead(waterSensors[2]) == 0) {
     int j = 0;
    while(j< 37){
      leds3[j] = CRGB::Black;
      j++;
    }
   }
  // Turn on fourth LED strip if fourth water sensor is in water:
   if (digitalRead(waterSensors[3]) != 0) {
    fadeToBlackBy( leds4, 37, 20);
    byte dothue = 0;
    for( int i = 0; i < 8; i++) {
      leds4[beatsin16( i+7, 0, 37-1 )] |= CHSV(dothue, 200, 255);
    
      dothue += 32;
    }
  }
  // Turn off fourth LED strip if fourth water sensor is not in water:
  else if (digitalRead(waterSensors[3]) == 0) {
     int j = 0;
      while(j< 37){
        leds4[j] = CRGB::Black;
        j++;
      }
   }

   // Read in a value from a photoresistor:
   int photocellReading = analogRead(lightCell); 
   // Map the value of light to a correct range:
   int LEDbrightness = map(photocellReading, 0, 1023, 255, 0);
   // Set the brightness of LED strips depending on the light level outside:
   FastLED.setBrightness(LEDbrightness);
   FastLED.show(); // Show the patterns assigned to LED strips
}
