#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

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

  void setupCams();
  void updateCams();
  void drawCams();

  void prepareDimensions();
  int calculateWidth();
  int calculateXOffset();

  ofVideoGrabber vidGrabber;
  vector<ofVideoGrabber> grabbers;

  int camWidth;
  int camHeight;
  int winWidth;
  int winHeight;
  int scaledWidth;
  int xOffset;

  int selected;
  int tiles;

  // MIDI
  void newMidiMessage(ofxMidiMessage& newMsg);
  void setupMidi();

  ofxMidiIn      midiIn;
};
