#include "Cameras.h"

void
Cameras::setup()
{
  arrangement = SINGLE;
  viewMode = SCALE;

  selected = 0;

  camWidth = 640;
  camHeight = 480;

  scaledWidth = calculateWidth();
  xOffset     = calculateXOffset();

  //we can now get back a list of devices.
  vector<ofVideoDevice> devices = initGrabber.listDevices();

  for(uint i = 0; i < devices.size(); i++){
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
  for(uint i = 0; i < grabbers.size(); i++){
    grabbers.at(i).update();
  }
}

void
Cameras::draw()
{
  ofSetHexColor(0xffffff);

  switch(arrangement) {
    case SINGLE:
      drawSingle();
      break;
    case DUAL_HORIZ:
      drawDual();
      break;
    case TRIPLE_HORIZ:
      drawTriple();
      break;
    case TILED:
      drawTiled();
      break;
  }

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

void
Cameras::setViewMode(ViewMode mode)
{
  viewMode = mode;

  switch(mode) {
    case CROP:
      cout << "View mode is now cropped;" << endl;
      break;
    case SCALE:
      cout << "View mode is now scaled" << endl;
      break;
  }
}

void
Cameras::setArrangement(Arrangement a)
{
  arrangement = a;

  switch(a) {
    case SINGLE:
      cout << "Arrangement is now single;" << endl;
      break;
    case DUAL_HORIZ:
      cout << "View mode is now dual (horiz)" << endl;
      break;
    case TRIPLE_HORIZ:
      cout << "View mode is now triple (horiz)" << endl;
      break;
    case TILED:
      cout << "View mode is now tiled" << endl;
      break;
  }
}


void
Cameras::setDimensions(int width, int height)
{
  winWidth  = width;
  winHeight = height;
  // scaledWidth = calculateWidth();
}

int
Cameras::getNumCameras()
{
  return grabbers.size();
}


int
Cameras::calculateXOffset()
{
  int out = 0;
  if(viewMode == SCALE) {
    out = (winWidth - scaledWidth) * 0.5;
  }
  return out;
}

int
Cameras::calculateYOffset()
{
  int out = 0;
  if(viewMode == CROP) {
    out = -((winHeight - scaledHeight) * 0.5);
  }
  return out;
}

int
Cameras::calculateWidth()
{
  int out = winWidth;
  if(viewMode == SCALE) {
    out = int((camWidth * 0.01f) * (winHeight / (camHeight * 0.01f)));
  }
  return out;
}

int
Cameras::calculateHeight()
{
  int out = winHeight;
  if(viewMode == CROP) {
    out = 0; // FIXME
  }
  return out;
}

void
Cameras::drawSingle()
{
  //grabbers.at(selected).draw(xOffset , 0, scaledWidth, winHeight);
  grabbers.at(selected).draw(0 , 0, camWidth, camHeight);
}

void
Cameras::drawDual()
{
}

void
Cameras::drawTriple()
{
}

void
Cameras::drawTiled()
{
}
