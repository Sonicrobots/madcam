#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  selected  = 0;

  winWidth = ofGetWidth();
  winHeight = ofGetHeight();

  camWidth  = 640; // try to grab at this size.
  camHeight = 480;

  scaledWidth = calculate_width();
  
  setup_cams();
}

//--------------------------------------------------------------
void ofApp::update(){
  ofBackground(0,0,0);
  update_cams();
}


//--------------------------------------------------------------
void ofApp::draw(){
  draw_cams();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key < 58 && key > 48) {
    selected = key - 49;
  } else {
    selected = 0;
  }
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
  scaledWidth = calculate_width();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::setup_cams()
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
  ofSetVerticalSync(true);
}

void ofApp::update_cams()
{ 
  grabbers.at(selected).update();
}


void ofApp::draw_cams()
{
  ofSetHexColor(0xffffff);
  grabbers.at(selected).draw(0, 0, scaledWidth, winHeight);
}


int ofApp::calculate_width()
{
  float scale = winHeight / (camHeight * 0.01f);
  return int((camWidth * 0.01f) * scale);
}

