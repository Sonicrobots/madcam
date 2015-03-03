#include "Cameras.h"

void
Cameras::setup()
{
  arrangement = SINGLE;
  viewMode = SCALE;

  onethird = int(1/3);
  twothirds = int(2/3);

  selected0 = 0;
  selected1 = 1;
  selected2 = 2;

  winWidth  = ofGetWidth();
  winHeight = ofGetHeight();

  camWidth  = 640;
  camHeight = 480;

  recalculate();

  ofVideoGrabber initGrabber;
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
    case MONOCLE:
      drawMonocle();
      break;
  }

  drawDebug();
}

void
Cameras::drawDebug()
{
  switch(arrangement) {
    case SINGLE:
      ofDrawBitmapString("Single",20,40);
      break;
    case DUAL_HORIZ:
      ofDrawBitmapString("Dual",20,40);
      break;
    case TRIPLE_HORIZ:
      ofDrawBitmapString("Triple",20,40);
      break;
    case TILED:
      ofDrawBitmapString("Tiled",20,40);
      break;
    case MONOCLE:
      ofDrawBitmapString("Monocle",20,40);
      break;
  }

  switch(viewMode) {
    case SCALE:
      ofDrawBitmapString("Scaled",20,60);
      break;
    case CROP:
      ofDrawBitmapString("Crop",20,60);
      break;
  }
}


void
Cameras::setCamera(int num)
{
  selected0 = num;
}

void
Cameras::setCamera(int slice, int num)
{
  switch(slice%3) {
    case 2:
      selected2 = num;
      break;
    case 1:
      selected1 = num;
      break;
    default:
      selected0 = num;
  }
}

void
Cameras::setViewMode(ViewMode mode)
{
  viewMode = mode;
  recalculate();
}

void
Cameras::setArrangement(Arrangement a)
{
  arrangement = a;
  recalculate();
}


void
Cameras::setDimensions(int width, int height)
{
  winWidth  = width;
  winHeight = height;
  recalculate();
}

int
Cameras::getNumCameras()
{
  return grabbers.size();
}

void
Cameras::recalculate()
{
  scaledHeight = calculateHeight();
  scaledWidth  = calculateWidth();
  xOffset = calculateXOffset();
  yOffset = calculateYOffset();

  //grabbers.at(selected).draw(xOffset , yOffset, scaledWidth, scaledHeight);
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
    out = (winHeight - scaledHeight) * 0.5;
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
    out = int((camHeight * 0.01f) * (winWidth / (camWidth * 0.01f)));
  }
  return out;
}


void
Cameras::drawSingle()
{
  grabbers.at(selected0).draw(xOffset , yOffset, scaledWidth, scaledHeight);
}

void
Cameras::drawDual()
{
  int sliceWidth = int(winWidth * 0.5);
  int offset0 = (scaledWidth - sliceWidth) * 0.5;

  grabbers.at(selected0).draw(-offset0, 0, scaledWidth, winHeight);
  grabbers.at(selected1)
      .getTextureReference()
      .drawSubsection(sliceWidth, 0, 0, scaledWidth, scaledHeight, 80, 0, 640, 480);
}

void
Cameras::drawTriple()
{
  int sliceWidth = int(winWidth * 0.3333333f);
  int offset0 = (scaledWidth - sliceWidth) * 0.5;

  //FIXME: offsets don't work out yet
  grabbers.at(selected0).draw(0, 0, scaledWidth, winHeight);
  grabbers.at(selected1).draw(sliceWidth, 0, scaledWidth, winHeight);
  grabbers.at(selected2).draw(sliceWidth * 2, 0, scaledWidth, winHeight);
}

void
Cameras::drawTiled()
{
  //int wsize   = winWidth / numTiles;
  //int hsize   = (wsize / (camWidth * 0.01)) * (0.01 * camHeight);
  //int numrows = winHeight / hsize;
  //int yoff    = 0;
  //for(int i = 0; i < numrows; i++) {
  //  for(int b = 0; b < numTiles; b++) {
  //    grabbers.at(i % grabbers.size()).draw(b*wsize,yoff,wsize,hsize);
  //  }
  //  yoff += hsize;
  //}
}


void
Cameras::drawMonocle()
{
}
