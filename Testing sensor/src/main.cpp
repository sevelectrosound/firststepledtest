#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=265,233.75
AudioOutputI2S           i2s1;           //xy=619,276
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=641.0000152587891,216.75000667572021
// GUItool: end automatically generated code
int treshold = 200;

void setup() 
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
  AudioMemory(20);   
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  waveform1.begin(WAVEFORM_SAWTOOTH);
  //waveform1.amplitude(0.75);
  waveform1.frequency(240.00);
  waveform1.pulseWidth(0.15);
  
}

float mapInput(int readValue)
{
  int avalue = map(readValue, 0, 1023, 1023,0);
  float result = ((avalue - treshold)/1023.00);
  Serial.println(result);
  return result;
}

void loop()
{
   digitalWrite(13, HIGH);
  // delay(300);
  // digitalWrite(13, LOW);
  // delay(300);
  // for(int freq = 50; freq <=500; freq++) {
  //   waveform1.frequency(freq);
  //   delay(10);
  //connect
  // }
  int pinValue = analogRead(22);
  // float value = mapInput(pinValue);
  // Serial.print("pinValue = ");
  // Serial.print(pinValue);
  // Serial.print("; value = ");
  // Serial.println(value);

  waveform1.amplitude(mapInput(pinValue));
  delay(100);
  
}