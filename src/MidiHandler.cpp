#include "MidiHandler.h"
#include "MadCam.h"

void
MidiHandler::registerHost(MadCam* app)
{
  application = app;

  midiIn.listPorts();

  vector<string> portList = midiIn.getPortList();

  for(int i = 0; i < portList.size(); i++) {
    //if(portList.at(i).compare(0, 9, "USB Uno MIDI Interface") == 0) {
    if(portList.at(i).compare(0, 9, "FastTrack") == 0) {
      cout << "opening " << portList.at(i) << endl;
      midiIn.openPort(portList.at(i));
      midiIn.addListener(this);
      midiIn.setVerbose(true);
      break;
    }
  }
  //midiIn.openPort(1);
  //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
  // don't ignore sysex, timing, & active sense messages,
  // these are ignored by default
  //midiIn.ignoreTypes(false, false, false);
}

void
MidiHandler::close()
{
  midiIn.closePort();
  midiIn.removeListener(this);
}

void
MidiHandler::newMidiMessage(ofxMidiMessage& msg)
{
  if(msg.channel == 2) {
    switch(msg.status) {
      case MIDI_NOTE_ON:
        //if(msg.pitch < grabbers.size())
          //selected = msg.pitch;
        // cout << "pitch: " << msg.pitch << endl;

        switch(msg.pitch) {
          // LAYOUT
          case 0:
            application->cameras.setLayout(SINGLE);
            break;
          case 1:
            application->cameras.setLayout(DUAL_HORIZ);
            break;
          case 2:
            application->cameras.setLayout(TRIPLE_HORIZ);
            break;
          case 3:
            application->cameras.setLayout(TILED);
            break;
          case 4:
            application->cameras.setLayout(MONOCLE);
            break;
        }

        // respond to mappings in notemap
        for(uint i = 0; i < application->config.noteMap.size(); i++) {
          auto mapping = application->config.noteMap.at(i);
          if(get<0>(mapping) == msg.pitch &&
             get<1>(mapping) >= 0         && 
	     get<1>(mapping) <  application->cameras.getNumCameras())
	  {
            application->cameras.trigger(std::get<1>(mapping));
            break;
          }
        }
        break;
    case MIDI_NOTE_OFF:
      break;
    case MIDI_PROGRAM_CHANGE:
      break;
    case MIDI_PITCH_BEND:
      break;
    case MIDI_AFTERTOUCH:
      break;
    case MIDI_POLY_AFTERTOUCH:
      break;
    case MIDI_SYSEX:
      break;
    case MIDI_TIME_CODE:
      break;
    case MIDI_SONG_POS_POINTER:
      break;
    case MIDI_SONG_SELECT:
      break;
    case MIDI_TUNE_REQUEST:
      break;
    case MIDI_SYSEX_END:
      break;
    case MIDI_TIME_CLOCK:
      break;
    case MIDI_START:
      break;
    case MIDI_CONTINUE:
      break;
    case MIDI_STOP:
      break;
    case MIDI_ACTIVE_SENSING:
      break;
    case MIDI_SYSTEM_RESET:
      break;
    default:
      break;
    }
  }

  if(msg.channel != 9) return;

  switch(msg.status) {
    case MIDI_CONTROL_CHANGE:

      // set camera in slot
      if(msg.control > 19 && msg.control < 30)
        application->cameras.setSlot(msg.control - 20, msg.value);

      // set decay
      if(msg.control == 30)
        application->cameras.setDecay(msg.value);

      // turn on trigger mode
      if(msg.control == 32) {
        if(msg.value < 64)
          application->cameras.setTriggerMode(true);
        else
          application->cameras.setTriggerMode(false);
      }

      // set camera in slot
      if(msg.control > 31 && msg.control < 41)
        application->cameras.setColorMode(msg.control - 32, msg.value);

    case MIDI_NOTE_OFF:
      break;
    case MIDI_PROGRAM_CHANGE:
      break;
    case MIDI_PITCH_BEND:
      break;
    case MIDI_AFTERTOUCH:
      break;
    case MIDI_POLY_AFTERTOUCH:
      break;
    case MIDI_SYSEX:
      break;
    case MIDI_TIME_CODE:
      break;
    case MIDI_SONG_POS_POINTER:
      break;
    case MIDI_SONG_SELECT:
      break;
    case MIDI_TUNE_REQUEST:
      break;
    case MIDI_SYSEX_END:
      break;
    case MIDI_TIME_CLOCK:
      break;
    case MIDI_START:
      break;
    case MIDI_CONTINUE:
      break;
    case MIDI_STOP:
      break;
    case MIDI_ACTIVE_SENSING:
      break;
    case MIDI_SYSTEM_RESET:
      break;
    default:
      break;
  }
}
