#ifndef MADCAM_CAMERAS_H
#define MADCAM_CAMERAS_H

#include "ofMain.h"
#include "Utils.h"

class Cameras {
public:
  void setup();
  void update();
  void draw();
  void setCamera(int num);
  void setCamera(int slice, int num);

  void setViewMode(ViewMode mode);
  void setArrangement(Arrangement arr);

  int getNumCameras();

  void setDimensions(int width, int height);

protected:

private:
  Arrangement arrangement;
  ViewMode viewMode;

  int numTiles;
  int selected;

  int camWidth;
  int camHeight;

  int winWidth;
  int winHeight;

  int scaledHeight;
  int scaledWidth;

  int yOffset;
  int xOffset;

  vector<ofVideoGrabber> grabbers;

  void recalculate();
  int calculateWidth();
  int calculateHeight();
  int calculateXOffset();
  int calculateYOffset();

  void drawSingle();
  void drawTiled();
  void drawDual();
  void drawTriple();

  void drawDebug();
};

#endif
