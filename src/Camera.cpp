#include "Camera.h"

void
Camera::setup(int camWidth, int camHeight)
{
  //ofEnableNormalizedTexCoords();
  amountX = 0;
  amountY = 0;

  colorMode = 0;
  decay = 8;

  useTrigger = false;

  // fade-out effect
  position = BUF_LEN - 1;
  initBuffer();
  blender.load("base.vert", "blender.frag");

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

  // START
  blender.begin();
  blender.setUniformTexture("tex1", grabber.getTextureReference(), 0);
  blender.setUniform1i("mode", colorMode);
  blender.setUniform1i("amountX", amountX);
  blender.setUniform1i("amountY", amountY);

  if(useTrigger)
    blender.setUniform1f("alpha", (curve[position] / 255.0f));
  else
    blender.setUniform1f("alpha", 1.0f);

  grabber.getTextureReference().drawSubsection(x, y, z, w, h, sx, sy, sw, sh);
  blender.end();
  // END

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
Camera::setFxAmount(int x, int y)
{
  amountX = x;
  amountY = y;
}

void
Camera::setColorMode(int mode)
{
  colorMode = mode;
}

void
Camera::setDecay(int dec)
{
  decay = -dec + 127;
}

void
Camera::reloadShader()
{
  cout << "reloading shader" << endl;
  blender.unload();
  blender.load("base.vert", "blender.frag");
}
