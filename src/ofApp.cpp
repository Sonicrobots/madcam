#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  camWidth  = 640; // try to grab at this size.
  camHeight = 480;

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

//--------------------------------------------------------------
void ofApp::update(){
  ofBackground(100,100,100);

  for (unsigned i=0; i< grabbers.size(); i++) {
    grabbers.at(i).update();
  }
}


//--------------------------------------------------------------
void ofApp::draw(){
  ofSetHexColor(0xffffff);
  for (unsigned i=0; i< grabbers.size(); i++) {
    grabbers.at(i).update();
    if(i < 3) {
      grabbers.at(i).draw((i % 3) * camWidth, 0);
    } else {
      grabbers.at(i).draw((i % 3) * camWidth, camHeight);
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
