#include "MidiHandler.h"
#include "MadCam.h"

void
MidiHandler::registerHost(MadCam* app)
{
  application = app;

  midiIn.listInPorts();

  vector<string> portList = midiIn.getInPortList();

  for(uint i = 0; i < portList.size(); i++) {
   // if(portList.at(i).compare(0, 22, "USB Uno MIDI Interface") == 0) {
    if(portList.at(i).compare(0, 24, "USB MS1x1 MIDI Interface") == 0) {
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
  if(msg.channel == 9) {
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
        if(msg.value > 1)
          application->cameras.setTriggerMode(true);
        else
          application->cameras.setTriggerMode(false);
      }

      if(msg.control == 33) {
        if(msg.value < 2)
          application->setFeedback(false);
        else
          application->setFeedback(true);
      }

      if(msg.control == 34) {
        application->setIterations(msg.value);
      }

      if(msg.control == 35) {
        application->setAlpha(msg.value);
      }

      if(msg.control == 36) {
        application->setXOffset(msg.value);
      }

      if(msg.control == 37)
        application->setYOffset(msg.value);

      // set camera in slot
      if(msg.control >= 40 && msg.control < 50)
        application->cameras.setColorMode(msg.control - 32, msg.value);

      if(msg.control == 50) 
        application->cameras.setXFxAmount(msg.value);

      if(msg.control == 51)
        application->cameras.setYFxAmount(msg.value);

      if(msg.control == 52)
        application->cameras.setXFxAmount(0, msg.value);

      if(msg.control == 53)
        application->cameras.setYFxAmount(0, msg.value);

      if(msg.control == 54)
        application->cameras.setXFxAmount(1, msg.value);

      if(msg.control == 55)
        application->cameras.setYFxAmount(1, msg.value);

      if(msg.control == 56)
        application->cameras.setXFxAmount(2, msg.value);

      if(msg.control == 57)
        application->cameras.setYFxAmount(2, msg.value);

      if(msg.control == 58)
        application->cameras.setXFxAmount(3, msg.value);

      if(msg.control == 59)
        application->cameras.setYFxAmount(3, msg.value);

      if(msg.control == 60)
        application->cameras.setXFxAmount(4, msg.value);

      if(msg.control == 61)
        application->cameras.setYFxAmount(4, msg.value);

      if(msg.control == 62)
        application->cameras.setXFxAmount(5, msg.value);

      if(msg.control == 63)
        application->cameras.setYFxAmount(5, msg.value);

      if(msg.control == 64)
        application->cameras.setXFxAmount(6, msg.value);

      if(msg.control == 65)
        application->cameras.setYFxAmount(6, msg.value);

      if(msg.control == 66)
        application->cameras.setXFxAmount(7, msg.value);

      if(msg.control == 67)
        application->cameras.setYFxAmount(7, msg.value);

      if(msg.control == 68)
        application->cameras.setXFxAmount(8, msg.value);

      if(msg.control == 69)
        application->cameras.setYFxAmount(8, msg.value);

      if(msg.control == 70)
        application->cameras.setSlot(msg.value);

      if(msg.control == 71)
        application->cameras.setSlot(0, msg.value);

      if(msg.control == 72)
        application->cameras.setSlot(1, msg.value);

      if(msg.control == 73)
        application->cameras.setSlot(2, msg.value);

      if(msg.control == 74)
        application->cameras.setSlot(3, msg.value);

      if(msg.control == 75)
        application->cameras.setSlot(4, msg.value);

      if(msg.control == 76)
        application->cameras.setSlot(5, msg.value);

      if(msg.control == 77)
        application->cameras.setSlot(6, msg.value);

      if(msg.control == 78)
        application->cameras.setSlot(7, msg.value);

      if(msg.control == 79)
        application->cameras.setSlot(8, msg.value);

      if(msg.control == 80)
        application->cameras.setColorMode(msg.value);

      if(msg.control == 80)
        application->cameras.setColorMode(msg.value);

      if(msg.control == 81)
        application->cameras.setColorMode(0, msg.value);

      if(msg.control == 82)
        application->cameras.setColorMode(1, msg.value);

      if(msg.control == 83)
        application->cameras.setColorMode(2, msg.value);

      if(msg.control == 84)
        application->cameras.setColorMode(3, msg.value);

      if(msg.control == 85)
        application->cameras.setColorMode(4, msg.value);

      if(msg.control == 86)
        application->cameras.setColorMode(5, msg.value);

      if(msg.control == 87)
        application->cameras.setColorMode(6, msg.value);

      if(msg.control == 88)
        application->cameras.setColorMode(7, msg.value);

      if(msg.control == 89)
        application->cameras.setColorMode(8, msg.value);

      if(msg.control == 90)
        application->setScene(msg.value);

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
