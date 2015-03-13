#ifndef MADCAM_MAIN_H
#define MADCAM_MAIN_H

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxXmlSettings.h"

#include "OscHandler.h"
#include "Utils.h"
#include "Camera.h"
#include "Cameras.h"


class MadCam : public ofBaseApp, public ofxMidiListener {

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

  // MIDI
  void newMidiMessage(ofxMidiMessage& newMsg);
  void setupMidi();

  OscHandler oscHandler;
  Cameras cameras;

  ofxXmlSettings XML;
  ofxMidiIn midiIn;

  void parseConfig();
  vector<tuple<int, int>> noteMap;
  vector<Scene> sceneMap;
};
#endif
