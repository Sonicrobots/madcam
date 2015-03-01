#include "ofMain.h"
#include "MadCam.h"

int main(){
	ofSetupOpenGL(1920,1080,OF_WINDOW); // OF_FULLSCREEN for show mode, OF_WINNDOW for dev
  ofSetWindowTitle("MadCam");
  ofSetWindowPosition(0,0);

  if(ofIsGLProgrammableRenderer()){
    cout << "gl3/shader: OK" << endl;
  } else {
    cout << "NOOOOOOOOOOOOOOO gl2/shader" << endl;
  }

	ofRunApp(new MadCam());
}
