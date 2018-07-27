#include <SoftSerial.h>     /* Use the digispark softserial library*/
#include <TinyPinChange.h> /* digispark softserial needs TinyPinchange */

#include <MIDI.h> // the 47effects midi library


SoftSerial softSerial(2,3);
    MIDI_CREATE_INSTANCE(SoftSerial, softSerial, MIDI);


//global variables
bool ClockRunning = false;
bool Paused = false;
bool Playing = false;

const int dr110SyncInputPin = 5; //Recieve the original TEMPO CLK from the dr110
const int dr110SyncOutPin = 1; //Send our new TEMPO CLK to the dr110
const int dr110StartPin = 2;   // Connect to the start button (active high)
const int dr110StopPin = 3;// Connect to the stop button (active high)
const int midiInputPin = 4;


 
const int dr110ClockTimeMs = 20; // the service manual states that clock pulse legnth(one full on-off cycle) can be from 17 -110 ms
const int ppqn = 12; //PulsesPerQuaterNote, for the dr110 there are 12 pulses per quater note.

// stuff for the led
unsigned long ledTimestamp = 0;
unsigned long ledTimer = 0;
int ledPin = 1;
    
void setup() {

pinMode(ledPin, OUTPUT);

  // setup the callbacks
MIDI.setHandleClock(MidiClock); //Callback for midi clock
MIDI.setHandleStart(MidiStart); //Callback for midi start
MIDI.setHandleStart(MidiStop); //Callback for midi stop
MIDI.setHandleStart(MidiContinue); //Callback for midi Continue

MIDI.begin(MIDI_CHANNEL_OMNI); // start midi, listening to all channels, it would be nice to switch this off(MIDI_CHANNEL_OFF) and only get channel ode messages.

flashled(10000);
}


void loop() {
  // run the midi callbacks...
  MIDI.read();
  handleLed();
}

void MidiClock(){
  
  }

void MidiStart(){
  Playing = true;
  ClockRunning = true;
   //send a Start event to the dr110
  }
  
void MidiStop(){
  Playing = false;
  ClockRunning = false;
  //send a stop event to the dr110
  }
  
void MidiContinue(){
  
  }  


void flashled(unsigned long ledmillis){
  //update timestamp
  ledTimestamp = millis();
  ledTimer = ledmillis;
}
  
void handleLed(){

  // get current time
unsigned long currentTime = millis();

  // is current current time - timestamp less than timer?

  if (currentTime - ledTimestamp < ledTimer){
    
    digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  // turn on led
  // else turn led off.
  
}
