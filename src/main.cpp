#include "ofMain.h"
#include "MadCam.h"

int main(){
	ofSetupOpenGL(1920,1080,OF_FULLSCREEN);
  ofSetWindowTitle("MadCam");
  ofSetWindowPosition(0,0);
	ofRunApp(new MadCam());
}
