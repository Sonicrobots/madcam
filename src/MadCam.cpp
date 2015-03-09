#include "MadCam.h"

//--------------------------------------------------------------
void MadCam::setup(){
  ofSetVerticalSync(true);
  setupMidi();
  cams.setup();
}

//--------------------------------------------------------------
void MadCam::update(){
  ofBackground(0,0,0);
  cams.update();
}

//--------------------------------------------------------------
void MadCam::draw(){
  cams.draw();
  ofDrawBitmapString(ofGetFrameRate(),20,20);
}

//--------------------------------------------------------------
void MadCam::keyPressed(int key){
  int baseKey = 49;

  if(key == 117)
    cams.toggleTrigger();

  if(key == 257)
    cams.trigger(0);

  if(key == 258)
    cams.trigger(1);

  if(key == 259)
    cams.trigger(2);

  if(key == 260)
    cams.trigger(3);

  // if(key >= baseKey && key < (baseKey + cams.getNumCameras())) {
  //   cams.setSlot((key % baseKey) % cams.getNumCameras());
  //   return;
  // }

  switch(key) {
    case 113:
      cams.setArrangement(SINGLE);
      break;
    case 119:
      cams.setArrangement(DUAL_HORIZ);
      break;
    case 101:
      cams.setArrangement(TRIPLE_HORIZ);
      break;
    case 114:
      cams.setArrangement(TILED);
      break;
    case 116:
      cams.setArrangement(MONOCLE);
      break;
    case 99:
      cams.setViewMode((CROP));
      break;
    case 115:
      cams.setViewMode((SCALE));
      break;
    case 54:
      cams.setColorMode(0);
      break;
    case 55:
      cams.setColorMode(1);
      break;
    case 56:
      cams.setColorMode(2);
      break;
    case 57:
      cams.setColorMode(3);
      break;
    case 48:
      cams.setColorMode(4);
      break;
    case 45:
      cams.setColorMode(5);
      break;
  }
}

//--------------------------------------------------------------
void
MadCam::windowResized(int w, int h)
{
  cams.setDimensions(w, h);
}

//--------------------------------------------------------------
void MadCam::exit() {
  // clean up
  midiIn.closePort();
  midiIn.removeListener(this);
}

// MIDI
void MadCam::setupMidi()
{
  midiIn.listPorts();

  vector<string> portList = midiIn.getPortList();

  for(int i = 0; i < portList.size(); i++) {
    if(portList.at(i).compare(0, 9, "FastTrack") == 0) {
      cout << "opening " << portList.at(i) << endl;
      midiIn.openPort(portList.at(i));
      midiIn.addListener(this);
      midiIn.setVerbose(true);
      return;
    }
  }

  //midiIn.openPort(1);
  //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
  // don't ignore sysex, timing, & active sense messages,
  // these are ignored by default
  //midiIn.ignoreTypes(false, false, false);
}

void MadCam::newMidiMessage(ofxMidiMessage& msg)
{
  if(msg.channel != 9) return;

  switch(msg.status) {
    case MIDI_NOTE_ON:
      //if(msg.pitch < grabbers.size())
        //selected = msg.pitch;
      // cout << "pitch: " << msg.pitch << endl;

      switch(msg.pitch) {
        // LAYOUT
        case 0:
          cams.setArrangement(SINGLE);
          break;
        case 1:
          cams.setArrangement(DUAL_HORIZ);
          break;
        case 2:
          cams.setArrangement(TRIPLE_HORIZ);
          break;
        case 3:
          cams.setArrangement(TILED);
          break;
        case 4:
          cams.setArrangement(MONOCLE);
          break;

      }

      if(msg.pitch >= 49 && msg.pitch < 60)
        cams.trigger(msg.pitch - 49);

      break;
    case MIDI_CONTROL_CHANGE:
      //cout << "ctrl: " << msg.control << " value: " << msg.value << endl;

      // Amount for all Cams simultaneously
      if(msg.control == 1)
        cams.setFxAmount(msg.value);

      // Amount per cam
      if(msg.control > 1 && msg.control < 20)
        cams.setFxAmount(msg.control % 10, msg.value);

      // set camera in slot
      if(msg.control > 19 && msg.control < 30)
        cams.setSlot(msg.control - 20, msg.value);

      // set decay
      if(msg.control == 30)
        cams.setDecay(msg.value);

      // turn on trigger mode
      if(msg.control == 32) {
        if(msg.value < 64)
          cams.setTriggerMode(true);
        else
          cams.setTriggerMode(false);
      }

      // set camera in slot
      if(msg.control > 31 && msg.control < 41)
        cams.setColorMode(msg.control - 32, msg.value);

      break;
    default:
      break;
  }
}

void MadCam::dragEvent(ofDragInfo dragInfo){}
void MadCam::keyReleased(int key){}
void MadCam::mouseMoved(int x, int y ){}
void MadCam::mouseDragged(int x, int y, int button){}
void MadCam::mousePressed(int x, int y, int button){}
void MadCam::mouseReleased(int x, int y, int button){}
void MadCam::gotMessage(ofMessage msg) {}
