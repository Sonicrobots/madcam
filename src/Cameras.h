#ifndef MADCAM_CAMERAS_H
#define MADCAM_CAMERAS_H

#include "ofMain.h"

class Cameras {
public:
  void setup();
  void update();
  void draw();
  void setCamera(int num);
  void setCamera(int slice, int num);

  void setDimensions(int width, int height);

protected:

private:
  int numTiles;
  int selected;
  int camWidth;
  int camHeight;
  int winWidth;
  int winHeight;
  int scaledWidth;
  int xOffset;

  ofVideoGrabber initGrabber;
  vector<ofVideoGrabber> grabbers;

  void prepareDimensions();
  int calculateWidth();
  int calculateXOffset();
};

#endif
