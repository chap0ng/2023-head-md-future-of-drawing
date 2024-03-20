/*
  // TCS230 color recognition sensor
  // Sensor connection pins to Arduino are shown in comments

  Color Sensor      Arduino
  -----------      --------
  VCC               5V
  GND               GND
  s0                8
  s1                9
  s2                12
  s3                11
  OUT               10
  OE                GND
*/
#include <MIDI.h>

const int s0 = 8;
const int s1 = 9;
const int s2 = 12;
const int s3 = 11;
const int out = 10;

// LED pins connected to Arduino
int redLed = 5;
int greenLed = 6;
int blueLed = 7;
// Variables
int red = 0;
int green = 0;
int blue = 0;
int indeks = 0;
const int rgbr = 7;
const int rgbg = 6;
const int rgbb = 5;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.begin();  // Launch MIDI and listen to channel 4

  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(rgbr, OUTPUT);
  pinMode(rgbg, OUTPUT);
  pinMode(rgbb, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
}

void loop() {
  color();

  int tmpr = (((20 - red) - 10) * 30);    //int tmpr=(((20-red)-10)*30);
  int tmpg = (((20 - green) - 10) * 30);  //int tmpg=(((20-green)-10)*30);
  int tmpb = (((20 - blue) - 10) * 30);   //int tmpb=(((20-blue)-10)*30);

  if (tmpr < 0)
    tmpr = 0;

  if (tmpg < 0)
    tmpg = 0;

  if (tmpb < 0)
    tmpb = 0;

  if (tmpg > tmpb && tmpg > tmpr) {
    tmpb = 0;
    tmpr = 0;
  }
  analogWrite(rgbr, tmpr);
  analogWrite(rgbg, tmpg);
  analogWrite(rgbb, tmpb);

  static uint8_t noteOn;

  if (tmpg > 149 && tmpg < 151) {
    static uint8_t noteOn = 0;
    if (!noteOn) {
      noteOn = true;
      MIDI.sendNoteOn(79, 127, 1);  // Send a Note (pitch 79, velo 127 on channel 1)
      MIDI.sendControlChange(64, 127, 1);
    }
  } else {
    static uint8_t noteOn = 1;
    if (noteOn) {
      noteOn = false;
      MIDI.sendNoteOff(79, 0, 1);  // Stop the note
      MIDI.sendControlChange(64, 0, 1);
    }
  }
}

void color() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED


  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}