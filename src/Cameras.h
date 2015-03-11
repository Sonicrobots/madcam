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

  void setViewMode(ViewMode mode);
  void setArrangement(Arrangement arr);

  int getNumCameras();

  void trigger();
  void trigger(int idx);

  void reset();
  void reset(int idx);

  void toggleTrigger();
  void setTriggerMode(bool mode);

  void reloadShaders();
  void setFxAmount(int xamount, int yamount);
  void setFxAmount(int idx, int xamount, int yamount);
  void setColorMode(int mode);
  void setColorMode(int idx, int mode);
  void setSlot(int cam);
  void setSlot(int idx, int cam);
  void setDecay(int decay);
  void setDimensions(int width, int height);

protected:

private:
  vector<int> slots;

  Arrangement arrangement;
  ViewMode viewMode;

  bool fxMode;
  bool triggerMode;

  int numTiles;

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
