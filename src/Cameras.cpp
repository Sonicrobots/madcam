#include "Cameras.h"

void
Cameras::setup()
{
  arrangement = SINGLE;
  viewMode = SCALE;

  fxMode = false;
  triggerMode = false;

  winWidth  = ofGetWidth();
  winHeight = ofGetHeight();

  camWidth  = 640;
  camHeight = 480;

  recalculate();

  ofVideoGrabber initGrabber;
  vector<ofVideoDevice> devices = initGrabber.listDevices();

  for(uint i = 0; i < devices.size(); i++){
    Camera grabber;
    grabber.setDeviceID(devices[i].id);
    grabber.setFPS(30);
    grabber.setup(camWidth,camHeight);
    cameras.push_back(grabber);
    slots.push_back(i);
  }
  
  cout << "---------------------- Cameras --------------------" << endl;
  cout << "# devices: " << devices.size() << endl;
  cout << "# grabbers: " << cameras.size() << endl;
  cout << "# slots: " << slots.size() << endl; 
}

void
Cameras::update()
{
  for(uint i = 0; i < cameras.size(); i++)
    cameras.at(i).update();
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
Cameras::setViewMode(ViewMode mode)
{
  viewMode = mode;
  recalculate();
}

void
Cameras::setArrangement(Arrangement a)
{
  reset();
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
  return cameras.size();
}

void
Cameras::recalculate()
{
  scaledHeight = calculateHeight();
  scaledWidth  = calculateWidth();
  xOffset = calculateXOffset();
  yOffset = calculateYOffset();
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
  cameras.at(slots.at(0))
      .draw(xOffset, yOffset, 0, scaledWidth, scaledHeight, 0, 0, camWidth, camHeight);
}

void
Cameras::drawDual()
{
  int sliceWidth = int(winWidth * 0.5);
  int offset0 = (scaledWidth - sliceWidth) * 0.5;

  cameras.at(slots.at(0))
      .draw(-offset0, 0, 0, scaledWidth, scaledHeight, 0, 0, camWidth, camHeight);
  ofSetColor(0,0, 0);
  ofRect(sliceWidth, 0, 0, sliceWidth, winHeight);
  cameras.at(slots.at(1))
      .draw(sliceWidth, 0, 0, scaledWidth, scaledHeight, 80, 0, camWidth, camHeight);
}

void
Cameras::drawTriple()
{
  int sliceWidth = int(winWidth * 0.3333333f);
  int offset0 = (scaledWidth - sliceWidth) * 0.5;
  int origoff0 = (offset0 / (scaledWidth * 0.01f)) * (camWidth * 0.01f);

  cameras.at(slots.at(0))
      .draw(-offset0, 0, 0, scaledWidth, scaledHeight, 0, 0, camWidth, camHeight);

  ofSetColor(0,0, 0);
  ofRect(sliceWidth, 0, 0, sliceWidth, winHeight);

  cameras.at(slots.at(1))
      .draw(sliceWidth, 0, 0, scaledWidth, scaledHeight, origoff0, 0, 640, 480);

  ofSetColor(0,0, 0);
  ofRect(sliceWidth * 2, 0, 0, sliceWidth, winHeight);

  cameras.at(slots.at(2))
      .draw(sliceWidth * 2, 0, 0, scaledWidth, scaledHeight, origoff0, 0, 640, 480);
}

void
Cameras::drawTiled()
{
  int tileheight = winHeight / 3;
  int tilewidth = (tileheight / (camHeight * 0.01f)) * (camWidth * 0.01f);
  int yoff = 0;
  int xoff = (winWidth - (tilewidth * 3)) * 0.5;

  for(uint i = 0; i < cameras.size(); i++) {
    cameras.at(i).draw(xoff + tilewidth * (i % 3), yoff, 0, tilewidth, tileheight, 0, 0, camWidth, camHeight);
    if(i % 3 == 2) yoff += tileheight;
  }
}


void
Cameras::drawMonocle()
{
  int tileheight = winHeight / 3;
  int tilewidth = (tileheight / (camHeight * 0.01f)) * (camWidth * 0.01f);
  int xoff = (winWidth - (tilewidth * 3)) * 0.5;

  cameras.at(slots.at(0)).draw(xoff,                 0, 0, tilewidth, tileheight, 0, 0, camWidth, camHeight);
  cameras.at(slots.at(1)).draw(xoff + tilewidth,     0, 0, tilewidth, tileheight, 0, 0, camWidth, camHeight);
  cameras.at(slots.at(2)).draw(xoff + tilewidth * 2, 0, 0, tilewidth, tileheight, 0, 0, camWidth, camHeight);
  cameras.at(slots.at(3)).draw(xoff, tileheight, 0, tilewidth * 2, tileheight * 2, 0, 0, camWidth, camHeight);
  cameras.at(slots.at(4)).draw(xoff + tilewidth * 2, tileheight, 0, tilewidth, tileheight, 0, 0, camWidth, camHeight);
  cameras.at(slots.at(5)).draw(xoff + tilewidth * 2, tileheight * 2, 0, tilewidth, tileheight, 0, 0, camWidth, camHeight);
}

void
Cameras::reset()
{
  for(uint i=0; i < cameras.size(); i++)
    cameras.at(i).reset();
}


void
Cameras::trigger()
{
  for(uint i=0; i < cameras.size(); i++)
    cameras.at(i).trigger();
}

void
Cameras::trigger(int idx)
{
  if(idx >= 0 && idx < cameras.size())
    cameras.at(idx).trigger();
}

void
Cameras::reset(int idx)
{
  if(idx >= 0 && idx < cameras.size())
    cameras.at(idx).reset();
}

void
Cameras::setTriggerMode(bool mode)
{
  for(uint i=0; i < cameras.size(); i++)
    cameras.at(i).setTriggerMode(mode);
}

void
Cameras::toggleTrigger()
{
  triggerMode = !triggerMode;
  for(uint i=0; i < cameras.size(); i++)
    cameras.at(i).setTriggerMode(triggerMode);
}

void
Cameras::setFxAmount(int idx, int xamount, int yamount)
{
  if(idx >= 0 && idx < cameras.size())
    cameras.at(idx).setFxAmount(xamount, yamount);
}

void
Cameras::setFxAmount(int xamount, int yamount)
{
  for(uint i=0; i < cameras.size(); i++)
    cameras.at(i).setFxAmount(xamount,yamount);
}

void
Cameras::setColorMode(int idx, int mode)
{
  if(idx >= 0 && idx < cameras.size())
    cameras.at(idx).setColorMode(mode);
}

void
Cameras::setColorMode(int mode)
{
  for(uint i=0; i < cameras.size(); i++)
    cameras.at(i).setColorMode(mode);
}

void
Cameras::setSlot(int cam)
{
  if(cam >= 0 && cam < cameras.size()) {
    for(uint i=0; i < cameras.size(); i++)
      slots[i] = cam;
  }
}

void
Cameras::setSlot(int idx, int cam)
{
  if((idx >= 0 && idx < cameras.size()) &&
     (cam >= 0 && cam < cameras.size()))
    slots[idx] = cam;
}

void
Cameras::setDecay(int decay)
{
  for(uint i=0; i < cameras.size(); i++)
    cameras.at(i).setDecay(decay);
}
