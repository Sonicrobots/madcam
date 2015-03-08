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

  cout << "key: " << key << endl;

  if(key == 265)
    cams.toggleFX();

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

  if(key >= baseKey && key < (baseKey + cams.getNumCameras())) {
    cams.setCamera((key % baseKey) % cams.getNumCameras());
    return;
  }

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
  }
}

//--------------------------------------------------------------
void MadCam::keyReleased(int key){

}

//--------------------------------------------------------------
void MadCam::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void MadCam::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void MadCam::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void MadCam::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void
MadCam::windowResized(int w, int h)
{
  cams.setDimensions(w, h);
}

//--------------------------------------------------------------
void
MadCam::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void MadCam::dragEvent(ofDragInfo dragInfo){

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
  midiIn.listPorts(); // via instance

  //midiIn.openPort(1);
  //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
  midiIn.openPort("FastTrack Pro 40:0");

  // don't ignore sysex, timing, & active sense messages,
  // these are ignored by default
  //midiIn.ignoreTypes(false, false, false);

  // add MadCam as a listener
  midiIn.addListener(this);
  midiIn.setVerbose(true);
}

void MadCam::newMidiMessage(ofxMidiMessage& msg)
{
  switch(msg.status) {
    case MIDI_NOTE_ON:
      //if(msg.pitch < grabbers.size())
        //selected = msg.pitch;
      cout << "pitch: " << msg.pitch << endl;
      return;
    case MIDI_CONTROL_CHANGE:
      if(msg.control == 20 && msg.value > 1)
        //tiles = msg.value;
      return;
    default:
      return;
  }
}
