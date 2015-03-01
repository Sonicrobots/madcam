#include "Cameras.h"

void
Cameras::setup()
{
  selected = 0;

  camWidth = 640;
  camHeight = 480;

  scaledWidth = calculateWidth();
  xOffset     = calculateXOffset();

  //we can now get back a list of devices.
  vector<ofVideoDevice> devices = initGrabber.listDevices();

  for(int i = 0; i < devices.size(); i++){
    ofVideoGrabber grabber;
    grabber.setDeviceID(devices[i].id);
    grabber.setDesiredFrameRate(30);
    grabber.setup(camWidth,camHeight);
    grabbers.push_back(grabber);
  }
}

void
Cameras::update()
{
  //if()
  //grabbers.at(selected).update();
  for(int i = 0; i < grabbers.size(); i++){
    grabbers.at(i).update();
  }
}

void
Cameras::draw()
{
  ofSetHexColor(0xffffff);
  //grabbers.at(selected).draw(xOffset , 0, scaledWidth, winHeight);
  grabbers.at(selected).draw(0 , 0, camWidth, camHeight);

  // int wsize   = winWidth / tiles;
  // int hsize   = (wsize / (camWidth * 0.01)) * (0.01 * camHeight);
  // int numrows = winHeight / hsize;
  // int yoff    = 0;
  // drawCams();
  //for(int i = 0; i < numrows; i++) {
  //  for(int b = 0; b < tiles; b++) {
  //    grabbers.at(i % grabbers.size()).draw(b*wsize,yoff,wsize,hsize);
  //  }
  //  yoff += hsize;
  //}
}


void
Cameras::setCamera(int num)
{
  selected = num;
}

void
Cameras::setCamera(int slice, int num)
{
  selected = num;
}


int
Cameras::calculateXOffset()
{
  return (winWidth - scaledWidth) / 2;
}

int
Cameras::calculateWidth()
{
  float scale = winHeight / (camHeight * 0.01f);
  return int((camWidth * 0.01f) * scale);
}
