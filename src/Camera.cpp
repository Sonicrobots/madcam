#include "Camera.h"

void
Camera::setup(int camWidth, int camHeight)
{
  //ofEnableNormalizedTexCoords();

  thresh = 0.0;
  decay = 8;

  useTrigger = false;

  position = BUF_LEN - 1;
  initBuffer();

  grabber.setDeviceID(device);
  grabber.setDesiredFrameRate(fps);
  grabber.setup(camWidth, camHeight);
}

void
Camera::setDeviceID(int id)
{
  device = id;
}

void
Camera::setFPS(int desiredFps)
{
  fps = desiredFps;
}

void
Camera::update()
{
  ofSetColor(255, 255, 255, 255);
  grabber.update();
}

void
Camera::draw(float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh)
{
  ofSetHexColor(0xffffff);
  ofEnableAlphaBlending();

  if(fx.isLoaded()) {
    fx.setUniformTexture("tex0", grabber.getTextureReference(), 1);
    fx.setUniform1f("threshold", thresh);
    fx.begin();
  }

  if(useTrigger) {
    ofSetColor(255, 255, 255, curve[position]);
  }

  grabber.getTextureReference().drawSubsection(x, y, z, w, h, sx, sy, sw, sh);

  ofSetColor(255, 255, 255, 255);

  if(fx.isLoaded()) {
    fx.end();
  }

  if(position < BUF_LEN -1) position += decay;
}

void
Camera::trigger()
{
  position = 0;
}

void
Camera::reset()
{
  position = BUF_LEN - 1;
}


void
Camera::initBuffer()
{
  for(int i = 0; i < 512; i++ ) {
    curve[i] = 255 * ( ((i / 512.0f) * -1.0f) + 1.0f );
  }
}

void
Camera::setTriggerMode(bool mode)
{
  useTrigger = mode;
}

void
Camera::setFXMode(bool mode)
{
  if(mode) {
    fx.load("base.vert", "threshold.frag");
  } else {
    fx.unload();
  }
}

void
Camera::setThreshold(float t)
{
  thresh = t;
}
