#ifndef MADCAM_MAIN_H
#define MADCAM_MAIN_H

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxXmlSettings.h"

#include "MidiHandler.h"
#include "OscHandler.h"
#include "Utils.h"
#include "Camera.h"
#include "Cameras.h"

class MadCam : public ofBaseApp {
  int currentCam;
  int iterations;
  int xoffset;
  int yoffset;
  int alpha;
  bool feedback;
  uint frameCount;

public:
  void setup();
  void update();
  void draw();
  void exit();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  void setScene(int idx);

  void dumpSettings();
  
  void setFeedback(bool mode);
  void setIterations(int iter);
  void setAlpha(int alpha);
  void setXOffset(int offs);
  void setYOffset(int offs);

  ofxXmlSettings XML;
  void parseConfig();

  ofFbo fbo;

  MidiHandler midiHandler;
  OscHandler oscHandler;
  Cameras cameras;
  Config config;
};
#endif
