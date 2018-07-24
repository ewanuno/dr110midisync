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
const int ledPin = 1;
long ledTimer = 0;
const long ledFlashTimeMs = 50; // how long to flash the led for
unsigned long ledTimerPrevious = 0;
bool ledState = 0;
    
void setup() {

  
  // setup the callbacks
MIDI.setHandleClock(MidiClock); //Callback for midi clock
MIDI.setHandleStart(MidiStart); //Callback for midi start
MIDI.setHandleStart(MidiStop); //Callback for midi stop
MIDI.setHandleStart(MidiContinue); //Callback for midi Continue

MIDI.begin(MIDI_CHANNEL_OMNI); // start midi, listening to all channels, it would be nice to switch this off(MIDI_CHANNEL_OFF) and only get channel ode messages.
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


void flashLed(unsigned long ledMillis){
  ledTimer = ledMillis;
  }
  
void handleLed(){

  //to turn the led on , just set it to a non zero value. it will turn off after that many milisecconds
  unsigned long ledTimerCurrent = millis();

 //update ledtimer
 ledTimer = ledTimer - (ledTimerCurrent-ledTimerPrevious);

 // check ledtimer is not zero.
 if (!(ledTimer > 0)){
  
  ledState = false;
  }
 //set led state.
  digitalWrite(ledPin, ledState);
    
  }
