#include "Camera.h"

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
Camera::setup(int camWidth, int camHeight)
{
  decay = 8;
  position = BUF_LEN - 1;

  initBuffer();

  grabber.setDeviceID(device);
  grabber.setDesiredFrameRate(fps);
  grabber.setup(camWidth, camHeight, OF_PIXELS_BGRA);

  tex.allocate(grabber.getWidth(), grabber.getHeight(), GL_RGB);

  pix = new unsigned char[ (int)( grabber.getWidth() * grabber.getHeight() * 3.0) ];
}

void
Camera::update()
{
  ofBackground(0, 0, 0, 0);

  grabber.update();

  if(grabber.isFrameNew()) {
    ofPixels & pixels = grabber.getPixels();
    unsigned char * src = pixels.getData();
    int totalPix = grabber.getWidth() * grabber.getHeight() * 3;

    for(int k = 0; k < totalPix; k+= 3){
      pix[k  ] = src[k] * curve[position];
      pix[k+1] = src[k+1] * curve[position];
      pix[k+2] = src[k+2] * curve[position];
    }

    tex.loadData(pix, grabber.getWidth(), grabber.getHeight(), GL_RGB);
  }
}

void
Camera::draw(float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh)
{
  ofSetHexColor(0xffffff);
  //tex.draw(0, 0, 1280, 960);
  tex.drawSubsection(x, y, z, w, h, sx, sy, sw, sh);
  if(position < BUF_LEN -1) position += decay;
}

void
Camera::trigger()
{
  position = 0;
}


void
Camera::initBuffer()
{
  for(int i = 0; i < 512; i++ ) {
    curve[i] = ((i / 512.0f) * -1.0f) + 1.0f;
  }
}
