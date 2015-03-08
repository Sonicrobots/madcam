#include "Camera.h"

void
Camera::setup(int camWidth, int camHeight)
{
  //ofEnableNormalizedTexCoords();

  swapMode = 2;
  thresh = 0.0;
  decay = 8;

  useTrigger = false;

  // fade-out effect
  position = BUF_LEN - 1;
  initBuffer();
  blender.load("base.vert", "blender.frag");
  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

  // zero out the framebuffer contents
  fbo.begin();
  ofClear(0, 0, 0, 0); // black is black is black is black
  fbo.end();

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

  blender.begin();
    blender.setUniformTexture("tex1", grabber.getTextureReference(), 0);
    blender.setUniform1i("mode", swapMode);
    blender.setUniform1f("threshold", thresh);

    if(useTrigger)
      blender.setUniform1f("amount", (curve[position] / 255.0f));
    else
      blender.setUniform1f("amount", 1.0f);

    grabber.getTextureReference().drawSubsection(x, y, z, w, h, sx, sy, sw, sh);
  blender.end();

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
    cout << "FX on" << endl;
    fx.load("base.vert", "swapchans.frag");
  } else {
    fx.unload();
  }
}

void
Camera::setThreshold(float t)
{
  thresh = t;
}

void
Camera::setSwapMode(int mode)
{
  swapMode = mode;
}
