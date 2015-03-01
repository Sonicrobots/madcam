#include "MadCam.h"

void MadCam::prepareDimensions()
{
  winWidth    = ofGetWidth();
  winHeight   = ofGetHeight();

  camWidth    = 640; // try to grab at this size.
  camHeight   = 480;

  scaledWidth = calculateWidth();
  xOffset     = calculateXOffset();
}

//--------------------------------------------------------------
void MadCam::setup(){
  selected  = 0;
  tiles     = 2;
  ofSetVerticalSync(true);
  prepareDimensions();
  setupCams();
  setupMidi();
}

//--------------------------------------------------------------
void MadCam::update(){
  ofBackground(0,0,0);
  updateCams();
}

//--------------------------------------------------------------
void MadCam::draw(){
  int wsize   = winWidth / tiles;
  int hsize   = (wsize / (camWidth * 0.01)) * (0.01 * camHeight);
  int numrows = winHeight / hsize;
  int yoff    = 0;
  drawCams();
  //for(int i = 0; i < numrows; i++) {
  //  for(int b = 0; b < tiles; b++) {
  //    grabbers.at(i % grabbers.size()).draw(b*wsize,yoff,wsize,hsize);
  //  }
  //  yoff += hsize;
  //}
}

//--------------------------------------------------------------
void MadCam::keyPressed(int key){
  cout << key << endl;
  if(key < 58 && key > 48) {
    selected = key - 49;
  } else {
    selected = 0;
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
void MadCam::windowResized(int w, int h){
  winWidth  = w;
  winHeight = h;
  scaledWidth = calculateWidth();
}

//--------------------------------------------------------------
void MadCam::gotMessage(ofMessage msg){

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


void MadCam::setupCams()
{
  //we can now get back a list of devices.
  vector<ofVideoDevice> devices = vidGrabber.listDevices();

  for(int i = 0; i < devices.size(); i++){
    ofVideoGrabber grabber;
    grabber.setDeviceID(devices[i].id);
    grabber.setDesiredFrameRate(30);
    grabber.setup(camWidth,camHeight);
    grabbers.push_back(grabber);
  }
}

void MadCam::updateCams()
{
  //if()
  //grabbers.at(selected).update();
  for(int i = 0; i < grabbers.size(); i++){
    grabbers.at(i).update();
  }
}


void MadCam::drawCams()
{
  ofSetHexColor(0xffffff);
  grabbers.at(selected).draw(xOffset , 0, scaledWidth, winHeight);
}

int MadCam::calculateXOffset()
{
  return (winWidth - scaledWidth) / 2;
}

int MadCam::calculateWidth()
{
  float scale = winHeight / (camHeight * 0.01f);
  return int((camWidth * 0.01f) * scale);
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
      if(msg.pitch < grabbers.size())
        selected = msg.pitch;
      return;
    case MIDI_CONTROL_CHANGE:
      if(msg.control == 20 && msg.value > 1)
        tiles = msg.value;
      return;
    default:
      return;
  }
}
