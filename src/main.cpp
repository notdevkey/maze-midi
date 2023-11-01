#include <Wire.h>
#include <MIDI.h>

#define MOMENTARY 0
#define LATCHING 1

// Define buttons
#define NUM_DI 12

#define DIGITAL_PIN_ORDER 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13

int velocity = 100; // velocity of MIDI notes, must be between 0 and 127
                    // higher velocity usually makes MIDI instruments louder

int noteON = 144;  // 144 = 10010000 in binary, note on command
int noteOFF = 128; // 128 = 10000000 in binary, note off command

byte digitalInputs[12];
byte digitalInputMapping[NUM_DI] = {DIGITAL_PIN_ORDER};

int tempDigitalInput;

MIDI_CREATE_DEFAULT_INSTANCE();

// Send MIDI message through USB port
void MIDImessage(int command, int MIDInote, int MIDIvelocity)
{
  Serial.write(command);      // send note on or note off command
  Serial.write(MIDInote);     // send pitch data
  Serial.write(MIDIvelocity); // send velocity data
}

const int CButtonPin = 2; // Change this to the appropriate pin
const int CsharpButtonPin = 4;

int rootNote = 60;
int cMajorIntervals[] = {78, 69, 54}; // Major scale intervals // C major ARP
int arpNoteCount = 3;
const int BPM = 150;
// int direction = 1; // 1 if up; 0 if down

void setup()
{
  // Initialize the button pin as an input
  pinMode(CButtonPin, INPUT_PULLUP);
  pinMode(CsharpButtonPin, INPUT_PULLUP);
  // Initialize MIDI
  MIDI.begin();
  Serial.begin(115200);
}

// Index of the current note in ARP(can't be higher than the selected ARP range length)
// Used to tell the controller which note to play next, instead of playing the whole ARP on a button press
int currentNoteInArp = 0;
int noteToPlay = 0;

void loop()
{
  // Read the button state
  int buttonState = digitalRead(CButtonPin);

  int noteCountPot = analogRead(A2);
  int arpSpeedPot = analogRead(A1);
  int gatePot = analogRead(A0);

  arpNoteCount = map(noteCountPot, 0, 1023, 3, 3);
  int arpSpeed = map(arpSpeedPot, 0, 1023, 10, 1000);
  int gatePercent = map(gatePot, 0, 1023, 1, 100);

  int noteDuration = (arpSpeed * gatePercent) / 100;

  // If the button is pressed (buttonState is LOW)
  if (buttonState == LOW)
  {
    // noteToPlay += cMajorIntervals[currentNoteInArp % sizeof(cMajorIntervals)];
    noteToPlay = cMajorIntervals[currentNoteInArp];

    // Send MIDI notes for the C major arpeggio
    MIDImessage(noteON, noteToPlay, velocity); // Send note on

    // How long the note should play
    delay(noteDuration);
    // Add gate(pause)
    MIDImessage(noteOFF, noteToPlay, 0); // Send note off
    delay(arpSpeed - noteDuration);
    if (currentNoteInArp < arpNoteCount - 1)
    {
      currentNoteInArp++;
    }
    else
    {
      noteToPlay = 0;
      currentNoteInArp = 0;
    }
  }
  else
  {
    noteToPlay = 0;
    currentNoteInArp = 0;
  }
  // Delay to prevent rapid triggering while button is held
  delay(1);
}
