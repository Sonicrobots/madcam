#ifndef MADCAM_CAMERAS_H
#define MADCAM_CAMERAS_H

#include "ofMain.h"
#include "Camera.h"
#include "Utils.h"

class Cameras {
public:
  void setup(vector<tuple<string,int>> camMap);
  void update();
  void draw();

  string getPhysicalPath(string device); 

  void setViewMode(ViewMode mode);
  void setLayout(Layout layout);

  int getNumCameras();

  void trigger();
  void trigger(int idx);

  void reset();
  void reset(int idx);

  void toggleTrigger();
  void setTriggerMode(bool mode);

  void reloadShaders();
  void setFxAmount(int xamount, int yamount);
  void setXFxAmount(int xamount);
  void setYFxAmount(int yamount);
  void setFxAmount(int idx, int xamount, int yamount);
  void setXFxAmount(int idx, int xamount);
  void setYFxAmount(int idx, int yamount);
  void setColorMode(int mode);
  void setColorMode(int idx, int mode);
  void setSlot(int cam);
  void setSlot(int idx, int cam);
  void setDecay(int decay);
  void setDimensions(int width, int height);

protected:

private:
  vector<int> slots;

  Layout layout;
  ViewMode viewMode;

  bool fxMode;
  bool triggerMode;

  tuple<int,uint> lastTrigger; 
  uint frameCount;
  uint triggerTimeout;

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
