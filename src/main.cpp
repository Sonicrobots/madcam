#include "ofMain.h"
#include "MadCam.h"

int main(){
  ofGLFWWindowSettings settings;

  // settings.width = 1440;
  // settings.height = 900;

  settings.width  = 1920;
  settings.height = 1080;

  settings.glVersionMajor = 4;
  settings.glVersionMinor = 4;

  ofCreateWindow(settings);

  // ofSetupOpenGL(1920,1080,OF_WINDOW); // OF_FULLSCREEN for show mode, OF_WINNDOW for dev
  // ofSetWindowTitle("MadCam");
  ofRunApp(new MadCam());
}
