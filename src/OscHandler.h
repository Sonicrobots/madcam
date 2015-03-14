#ifndef  OSC_HANDLER_H
#define  OSC_HANDLER_H

#include "ofxOsc.h"

class MadCam;

class OscHandler
{
  ofxOscReceiver receiver;
  MadCam *application = NULL;

public:
  void registerHost(MadCam *app);
  void process();
};

#endif


