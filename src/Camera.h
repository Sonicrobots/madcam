#ifndef MADCAM_CAMERA_H
#define MADCAM_CAMERA_H

#include "ofMain.h"
#include "Utils.h"


class Camera {
public:
  void setup();
  void update();
  void draw();
  void trigger();
protected:

private:
  static const int BUF_LEN = 512;

  int decay;
  int position;

  ofTexture tex;
  ofVideoGrabber grabber;

  void initBuffer();

  unsigned char * pix;

  std::array<float, BUF_LEN> curve;
};

#endif
