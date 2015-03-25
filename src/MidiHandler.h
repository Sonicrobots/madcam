#ifndef MADCAM_MIDI_HANDLER_H
#define MADCAM_MIDI_HANDLER_H

#include "ofxMidi.h"
#include "Utils.h"

class MadCam;

class MidiHandler : public ofxMidiListener  {
  ofxMidiIn midiIn;
  MadCam* application = NULL;

public:
  void registerHost(MadCam* app);
  void newMidiMessage(ofxMidiMessage& newMsg);
  void close();
};

#endif
