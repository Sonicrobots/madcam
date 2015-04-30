#include "OscHandler.h"
#include "MadCam.h"

void
OscHandler::registerHost(MadCam *app)
{
  receiver.setup(8080);
  application = app;
}

void
OscHandler::process()
{
  if(application == NULL) return;

  while(receiver.hasWaitingMessages()) {
    // the th
    ofxOscMessage m;
    receiver.getNextMessage(&m);

    string addr = m.getAddress();
    cout << "Message for address: " << addr << endl;

    if(addr == "/trigger/state") {
      if(m.getArgAsInt32(0) % 2 == 0)
        application->cameras.setTriggerMode(false);
      else
        application->cameras.setTriggerMode(true);
    }

    if(addr == "/trigger")
      application->cameras.trigger(m.getArgAsInt32(0));

    if(addr == "/layout") {
      switch(m.getArgAsInt32(0)) {
        case 0:
          application->cameras.setLayout(SINGLE);
          break;
        case 1:
          application->cameras.setLayout(DUAL_HORIZ);
          break;
        case 2:
          application->cameras.setLayout(TRIPLE_HORIZ);
          break;
        case 3:
          application->cameras.setLayout(TILED);
          break;
        case 4:
          application->cameras.setLayout(MONOCLE);
          break;
      }
    }

    if(addr == "/decay")
      application->cameras.setDecay(m.getArgAsInt32(0));

    if(addr == "/fbo") {
      if(m.getArgAsInt32(0) == 0)
        application->setFeedback(false);
      else
        application->setFeedback(true);
    }

    if(addr == "/iterations")
      application->setIterations(m.getArgAsInt32(0));

    if(addr == "/alpha")
      application->setAlpha(m.getArgAsInt32(0));

    if(addr == "/xoffset")
      application->setXOffset(m.getArgAsInt32(0));

    if(addr == "/yoffset")
      application->setYOffset(m.getArgAsInt32(0));

    if(addr == "/fx/amount/global")
      application->cameras.setFxAmount(m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/fx/amount/0")
      application->cameras.setFxAmount(0 ,m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/fx/amount/1")
      application->cameras.setFxAmount(1 ,m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/fx/amount/2")
      application->cameras.setFxAmount(2 ,m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/fx/amount/3")
      application->cameras.setFxAmount(3 ,m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/fx/amount/4")
      application->cameras.setFxAmount(4 ,m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/fx/amount/5")
      application->cameras.setFxAmount(5 ,m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/fx/amount/6")
      application->cameras.setFxAmount(6 ,m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/fx/amount/7")
      application->cameras.setFxAmount(7 ,m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/fx/amount/8")
      application->cameras.setFxAmount(8 ,m.getArgAsInt32(0), m.getArgAsInt32(1));

    if(addr == "/slot/global")
      application->cameras.setSlot(m.getArgAsInt32(0));

    if(addr == "/slot/0")
      application->cameras.setSlot(0 ,m.getArgAsInt32(0));

    if(addr == "/slot/1")
      application->cameras.setSlot(1 ,m.getArgAsInt32(0));

    if(addr == "/slot/2")
      application->cameras.setSlot(2 ,m.getArgAsInt32(0));

    if(addr == "/slot/3")
      application->cameras.setSlot(3 ,m.getArgAsInt32(0));

    if(addr == "/slot/4")
      application->cameras.setSlot(4 ,m.getArgAsInt32(0));

    if(addr == "/slot/5")
      application->cameras.setSlot(5 ,m.getArgAsInt32(0));

    if(addr == "/slot/6")
      application->cameras.setSlot(6 ,m.getArgAsInt32(0));

    if(addr == "/slot/7")
      application->cameras.setSlot(7 ,m.getArgAsInt32(0));

    if(addr == "/slot/8")
      application->cameras.setSlot(8 ,m.getArgAsInt32(0));

    if(addr == "/color/global")
      application->cameras.setColorMode(m.getArgAsInt32(0));

    if(addr == "/color/0")
      application->cameras.setColorMode(0 ,m.getArgAsInt32(0));

    if(addr == "/color/1")
      application->cameras.setColorMode(1 ,m.getArgAsInt32(0));

    if(addr == "/color/2")
      application->cameras.setColorMode(2 ,m.getArgAsInt32(0));

    if(addr == "/color/3")
      application->cameras.setColorMode(3 ,m.getArgAsInt32(0));

    if(addr == "/color/4")
      application->cameras.setColorMode(4 ,m.getArgAsInt32(0));

    if(addr == "/color/5")
      application->cameras.setColorMode(5 ,m.getArgAsInt32(0));

    if(addr == "/color/6")
      application->cameras.setColorMode(6 ,m.getArgAsInt32(0));

    if(addr == "/color/7")
      application->cameras.setColorMode(7 ,m.getArgAsInt32(0));

    if(addr == "/color/8")
      application->cameras.setColorMode(8 ,m.getArgAsInt32(0));

    if(addr == "/scene")
      application->setScene(m.getArgAsInt32(0));
  }
}
