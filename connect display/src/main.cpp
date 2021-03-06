#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Fonts/FreeSerif18pt7b.h>  // Add a custom font

#include <Audio.h>
//#include <SD.h>
//#include <SerialFlash.h>

// Declare pins for the display:
#define TFT_CS     14
#define TFT_RST    10  // You can also connect this to the Arduino reset in which case, set this #define pin to -1!
#define TFT_DC     15
// The rest of the pins are pre-selected as the default hardware SPI for Arduino Uno (SCK = 13 and SDA = 11)
// Create display:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=265,233.75
AudioOutputI2S           i2s1;           //xy=619,276
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=641.0000152587891,216.75000667572021
// GUItool: end automatically generated code

int Variable1;  // Create a variable to have something dynamic to show on the display
int treshold = 200;
float a = 0;
int atreshold()
{
  int a22 = analogRead(22);  
  int avalue = map(a22, 0, 1023, 1023,0);
  return avalue;
}
void setup()  // Start of setup
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(22, INPUT_PULLUP);
  digitalWrite(13, HIGH);
  digitalWrite(0,LOW);
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  treshold = atreshold();
  
  AudioMemory(20);   
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  waveform1.begin(WAVEFORM_SAWTOOTH);
  //waveform1.amplitude(0.75);
  waveform1.frequency(240.00);
  waveform1.pulseWidth(0.15);

  // Display setup:

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab

  tft.fillScreen(ST7735_BLACK);  // Fill screen with black

  //tft.setRotation(0);  // Set orientation of the display. Values are from 0 to 3. If not declared, orientation would be 0,
                         // which is portrait mode.

  tft.setTextWrap(false);  // By default, long lines of text are set to automatically ???wrap??? back to the leftmost column.
                           // To override this behavior (so text will run off the right side of the display - useful for
                           // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                           // with setTextWrap(true).




  // We are going to print on the display everything that is static on the setup, to leave the loop free for dynamic elements:

  // Write to the display the text "Hello":
  tft.setCursor(0, 0);  // Set position (x,y)
  tft.setTextColor(ST7735_WHITE);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(4);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(treshold);  // Print a text or value

  
  
  // Start using a custom font:
  tft.setFont(&FreeSerif18pt7b);  // Set a custom font
  tft.setTextSize(0);  // Set text size. We are using custom font so you should always set text size as 0

  // Write to the display the text "World":
  tft.setCursor(0, 50);  // Set position (x,y)
  tft.setTextColor(ST7735_RED);  // Set color of text. We are using custom font so there is no background color supported
  tft.println("World!");  // Print a text or value

  // Stop using a custom font:
  tft.setFont();  // Reset to standard font, to stop using any custom font previously set




  // Draw rectangle:
  tft.drawRect(0, 60, 60, 30, ST7735_CYAN);  // Draw rectangle (x,y,width,height,color)
                                             // It draws from the location to down-right
                                             
  // Draw rounded rectangle:
  tft.drawRoundRect(68, 60, 60, 30, 10, ST7735_CYAN);  // Draw rounded rectangle (x,y,width,height,radius,color)
                                                       // It draws from the location to down-right


  // Draw triangle:
  tft.drawTriangle(60,120,    70,94,    80,120, ST7735_YELLOW);  // Draw triangle (x0,y0,x1,y1,x2,y2,color)


  // Draw filled triangle:
  tft.fillTriangle(100,120,    110,94,    120,120, ST7735_CYAN);  // Draw filled triangle (x0,y0,x1,y1,x2,y2,color)


  // Draw line:
  tft.drawLine(0, 125, 127, 125, ST7735_CYAN);  // Draw line (x0,y0,x1,y1,color)
  

  //  Draw circle:
  tft.drawCircle(15, 144, 14, ST7735_GREEN);  //  Draw circle (x,y,radius,color)


  // Draw a filled circle:
  tft.fillCircle(60, 144, 14, ST7735_BLUE);  // Draw circle (x,y,radius,color)


  // Draw rounded rectangle and fill:
  tft.fillRoundRect(88, 130, 40, 27, 5, 0xF81B);  // Draw rounded filled rectangle (x,y,width,height,color)
  
}  // End of setup


float mapInput(int readValue)
{
  digitalWrite(13, HIGH);
  int avalue = map(readValue, 0, 1023, 1023,0);
  float result = ((avalue - treshold)/1023.00);
  Serial.println(result);
  return result;
}


int adc()
{
  digitalWrite(13, HIGH);
  int a22 = analogRead(22);  
  int avalue = map(a22, 0, 1023, 1023,0);
  int result = (avalue - treshold);
  Serial.println(result);
  digitalWrite(13, LOW);
  return result;
}

void loop()  // Start of loop
{

  Variable1++;  // Increase variable by 1
  if(Variable1 > 150)  // If Variable1 is greater than 150
  {
    Variable1 = 0;  // Set Variable1 to 0
  }
  //int pinValue = analogRead(22);

  // Convert Variable1 into a string, so we can change the text alignment to the right:
  // It can be also used to add or remove decimal numbers.
  char string[10];  // Create a character array of 10 characters
  // Convert float to a string:
  dtostrf(Variable1, 3, 0, string);  // (<variable>,<amount of digits we are going to use>,<amount of decimal digits>,<string name>)


  // We are going to print on the display everything that is dynamic on the loop, to refresh continuously:

// ?????????? ????????????
  // Write to the display the Variable1 with left text alignment:
  tft.setCursor(13, 67);  // Set position (x,y)
  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(555);  // Print a text or value
  // tft.println(Variable1);  // Print a text or value
  
  // There is a problem when we go, for example, from 100 to 99 because it doesn't automatically write a background on
  // the last digit we are not longer refreshing. We need to check how many digits are and fill the space remaining.
  if(Variable1 < 10)  // If Variable1 is less than 10...
  {
    // Fill the other digit with background color:
    tft.fillRect(23, 67, 12, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  }
  if(Variable1 < 100)  // If Variable1 is less than 100...
  {
    // Fill the other digit with background color:
    tft.fillRect(36, 67, 12, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  }



//???????????? ????????????
  // Write to the display the string with right text alignment:
  tft.setCursor(81, 67);  // Set position (x,y)
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  // tft.println(999);  // Print a text or value
  Variable1 = adc();
  a = mapInput(Variable1);
  tft.println(a);  // Print a text or value

  // We are going to write the Variable1 with a custom text, so you can see the issues:
  
  // Draw a black square in the background to "clear" the previous text:
  // This is because we are going to use a custom font, and that doesn't support brackground color.
  // We are basically printing our own background. This will cause flickering, though.
  tft.fillRect(0, 90, 55, 34, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)


  // Start using a custom font:
  tft.setFont(&FreeSerif18pt7b);  // Set a custom font
  tft.setTextSize(0);  // Set text size. We are using custom font so you should always set text size as 0

 // ?????????? ??????????
  // Write to the display the Variable1:
  tft.setCursor(0, 120);  // Set position (x,y)
  tft.setTextColor(ST7735_MAGENTA);  // Set color of text. We are using custom font so there is no background color supported
  // tft.println(777);  // Print a text or value
  
  tft.println(Variable1);  // Print a text or value

  // Stop using a custom font:
  tft.setFont();  // Reset to standard font, to stop using any custom font previously set
  int pinValue = analogRead(22);
  waveform1.amplitude(mapInput(pinValue));
  delay(10);
}  // End of loop