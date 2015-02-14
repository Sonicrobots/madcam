#include "ofApp.h"

void ofApp::prepareDimensions()
{
  winWidth    = ofGetWidth();
  winHeight   = ofGetHeight();

  camWidth    = 640; // try to grab at this size.
  camHeight   = 480;
 
  scaledWidth = calculateWidth();
  xOffset     = calculateXOffset();
}

//--------------------------------------------------------------
void ofApp::setup(){
  selected  = 0;
  ofSetVerticalSync(true);
  prepareDimensions();
  setupCams();
  setupMidi();
}

//--------------------------------------------------------------
void ofApp::update(){
  ofBackground(0,0,0);
  updateCams();
}


//--------------------------------------------------------------
void ofApp::draw(){
  drawCams();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  cout << key << endl;
  // if(key < 58 && key > 48) {
  //   selected = key - 49;
  // } else {
  //   selected = 0;
  // }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
  winWidth  = w;
  winHeight = h;
  scaledWidth = calculateWidth();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}


void ofApp::setupCams()
{
  //we can now get back a list of devices.
  vector<ofVideoDevice> devices = vidGrabber.listDevices();

  for(int i = 0; i < devices.size(); i++){
    cout << devices[i].id << ": " << devices[i].deviceName;
    
    ofVideoGrabber grabber;
    grabber.setDeviceID(devices[i].id);
    grabber.setDesiredFrameRate(30);
    grabber.setup(camWidth,camHeight);

    grabbers.push_back(grabber);
    
    if( devices[i].bAvailable ){
      cout << endl;
    }else{
      cout << " - unavailable " << endl;
    }
  }
}

void ofApp::updateCams()
{ 
  grabbers.at(selected).update();
}


void ofApp::drawCams()
{
  ofSetHexColor(0xffffff);
  grabbers.at(selected).draw(xOffset , 0, scaledWidth, winHeight);
}

int ofApp::calculateXOffset()
{
  return (winWidth - scaledWidth) / 2;
}

int ofApp::calculateWidth()
{
  float scale = winHeight / (camHeight * 0.01f);
  return int((camWidth * 0.01f) * scale);
}


// MIDI
void ofApp::setupMidi()
{
  // print input ports to console
	midiIn.listPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well
	
	// open port by number (you may need to change this)
	//midiIn.openPort(1);
	//midiIn.openPort("IAC Pure Data In");	// by name
  midiIn.openPort("FastTrack Pro 40:0");

	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	midiIn.setVerbose(true);
}

void ofApp::newMidiMessage(ofxMidiMessage& msg)
{
  switch(msg.status) {
    case MIDI_NOTE_ON:
      selected = msg.pitch % grabbers.size();
      return;
    default:
      return;
  }
}
