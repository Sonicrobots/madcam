#ifndef MADCAM_CAMERA_H
#define MADCAM_CAMERA_H

#include "ofMain.h"
#include "Utils.h"


class Camera {
public:
  void update();
  void setup(int camWidth, int camHeight);
  void draw(float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh);

  void trigger();
  void reset();

  void setColorMode(int mode);
  void setFxAmount(int xamount, int yamount);
  void setTriggerMode(bool on);
  void setDeviceID(int id);
  void setFPS(int fps);
  void setDecay(int decay);
protected:

private:
  static const int BUF_LEN = 512;

  bool useTrigger;

  int device;
  int fps;
  int decay;
  int position;

  int colorMode;
  int amount;

  ofShader blender;
  ofVideoGrabber grabber;

  void initBuffer();

  unsigned char * pix;

  std::array<int, BUF_LEN> curve;
};

#endif
