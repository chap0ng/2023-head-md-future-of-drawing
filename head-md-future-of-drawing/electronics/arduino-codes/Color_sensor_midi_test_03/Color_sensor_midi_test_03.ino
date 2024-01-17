#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibration Values
// *Get these from Calibration Sketch
int redMin = 47;    // Red minimum value
int redMax = 239;   // Red maximum value
int greenMin = 49; // Green minimum value
int greenMax = 231; // Green maximum value
int blueMin = 37;  // Blue minimum value
int blueMax = 251;  // Blue maximum value

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

void setup() {
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Setup MIDI
  MIDI.begin();
}

void loop() {
  // Read Red value
  redPW = getRedPW();
  // Map to value from 0-127 (MIDI range)
  redValue = map(redPW, redMin, redMax, 0, 127);
  redValue = constrain(redValue, 0, 127); // Ensure redValue stays between 0 and 127
  // Delay to stabilize sensor
  delay(200);

  // Read Green value
  greenPW = getGreenPW();
  // Map to value from 0-127 (MIDI range)
  greenValue = map(greenPW, greenMin, greenMax, 0, 127);
  greenValue = constrain(greenValue, 0, 127); // Ensure greenValue stays between 0 and 127
  // Delay to stabilize sensor
  delay(200);

  // Read Blue value
  bluePW = getBluePW();
  // Map to value from 0-127 (MIDI range)
  blueValue = map(bluePW, blueMin, blueMax, 0, 127);
  blueValue = constrain(blueValue, 0, 127); // Ensure blueValue stays between 0 and 127
  // Delay to stabilize sensor
  delay(200);

  // Print output to Serial Monitor
  Serial.print("Red = ");
  Serial.print(redValue);
  Serial.print(" - Green = ");
  Serial.print(greenValue);
  Serial.print(" - Blue = ");
  Serial.println(blueValue);

  // Send MIDI messages
  sendMIDI(redValue, 1);    // MIDI channel 1 for Red
  sendMIDI(greenValue, 2);  // MIDI channel 2 for Green
  sendMIDI(blueValue, 3);   // MIDI channel 3 for Blue
}

// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to send MIDI Note On messages
void sendMIDI(int value, int channel) {
  int noteNumber = 60 + channel;  // Adjust the MIDI Note number based on the channel
  MIDI.sendNoteOn(noteNumber, value, channel);
  delay(100); // Add a delay to avoid sending too many MIDI messages in a short time
  MIDI.sendNoteOff(noteNumber, 0, channel);
}