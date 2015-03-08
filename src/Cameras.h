#ifndef MADCAM_CAMERAS_H
#define MADCAM_CAMERAS_H

#include "ofMain.h"
#include "Camera.h"
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

  void trigger();
  void trigger(int idx);

  void reset();
  void reset(int idx);

  void toggleTrigger();
  void setTriggerMode(bool mode);

  void toggleFX();
  void setFXMode(bool mode);
  void setSwapMode(int mode);

  void setDimensions(int width, int height);

protected:

private:
  Arrangement arrangement;
  ViewMode viewMode;

  bool fxMode;
  bool triggerMode;

  int numTiles;

  int selected0;
  int selected1;
  int selected2;
  int selected3;
  int selected4;
  int selected5;

  int camWidth;
  int camHeight;

  int winWidth;
  int winHeight;

  int scaledHeight;
  int scaledWidth;

  int yOffset;
  int xOffset;

  vector<Camera> cameras;

  void recalculate();
  int calculateWidth();
  int calculateHeight();
  int calculateXOffset();
  int calculateYOffset();

  void drawSingle();
  void drawTiled();
  void drawDual();
  void drawTriple();
  void drawMonocle();

  void drawDebug();
};

#endif
