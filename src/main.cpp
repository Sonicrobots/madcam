#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1920,1080,OF_FULLSCREEN);			// <-------- setup the GL context
  ofSetWindowTitle("MadCam");
	ofRunApp(new ofApp());
}
