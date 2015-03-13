#include "OscHandler.h"
#include "MadCam.h"

void
OscHandler::registerHost(MadCam *app)
{
  receiver.setup(8080);
  application = app;
  cout << "registered OSC host " << application << endl;
}

void
OscHandler::process()
{
  if(application == NULL) return;

  while(receiver.hasWaitingMessages()) {

    ofxOscMessage m;
    receiver.getNextMessage(&m);

    string addr = m.getAddress();

    cout << "Message for address: " << addr << endl;

    if(addr == "/trigger/state") {
      if(m.getArgAsInt32(0) % 2 == 0) {
        application->cameras.setTriggerMode(false);
        cout << "trigger mode off" << endl;
      } else {
        application->cameras.setTriggerMode(true);
        cout << "trigger mode on" << endl;
      }
    }

    if(addr == "/trigger") {
      application->cameras.trigger(m.getArgAsInt32(0));
      cout << "trigger cam: " << m.getArgAsInt32(0) << endl;
    }

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
      cout << "layout: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/decay") {
      application->cameras.setDecay(m.getArgAsInt32(0));
      cout << "decay: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/global") {
      application->cameras.setFxAmount(m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "global fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/0") {
      application->cameras.setFxAmount(0 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 0 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/1") {
      application->cameras.setFxAmount(1 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 1 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/2") {
      application->cameras.setFxAmount(2 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 2 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/3") {
      application->cameras.setFxAmount(3 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 3 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/4") {
      application->cameras.setFxAmount(4 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 4 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/5") {
      application->cameras.setFxAmount(5 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 5 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/6") {
      application->cameras.setFxAmount(6 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 6 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/7") {
      application->cameras.setFxAmount(7 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 7 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/8") {
      application->cameras.setFxAmount(8 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 8 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/slot/global") {
      application->cameras.setSlot(m.getArgAsInt32(0));
      cout << "cam globa; slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/0") {
      application->cameras.setSlot(0 ,m.getArgAsInt32(0));
      cout << "cam 0 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/1") {
      application->cameras.setSlot(1 ,m.getArgAsInt32(0));
      cout << "cam 1 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/2") {
      application->cameras.setSlot(2 ,m.getArgAsInt32(0));
      cout << "cam 2 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/3") {
      application->cameras.setSlot(3 ,m.getArgAsInt32(0));
      cout << "cam 3 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/4") {
      application->cameras.setSlot(4 ,m.getArgAsInt32(0));
      cout << "cam 4 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/5") {
      application->cameras.setSlot(5 ,m.getArgAsInt32(0));
      cout << "cam 5 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/6") {
      application->cameras.setSlot(6 ,m.getArgAsInt32(0));
      cout << "cam 6 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/7") {
      application->cameras.setSlot(7 ,m.getArgAsInt32(0));
      cout << "cam 7 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/8") {
      application->cameras.setSlot(8 ,m.getArgAsInt32(0));
      cout << "cam 8 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/global") {
      application->cameras.setColorMode(m.getArgAsInt32(0));
      cout << "cam 0 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/0") {
      application->cameras.setColorMode(0 ,m.getArgAsInt32(0));
      cout << "cam 0 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/1") {
      application->cameras.setColorMode(1 ,m.getArgAsInt32(0));
      cout << "cam 1 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/2") {
      application->cameras.setColorMode(2 ,m.getArgAsInt32(0));
      cout << "cam 2 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/3") {
      application->cameras.setColorMode(3 ,m.getArgAsInt32(0));
      cout << "cam 3 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/4") {
      application->cameras.setColorMode(4 ,m.getArgAsInt32(0));
      cout << "cam 4 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/5") {
      application->cameras.setColorMode(5 ,m.getArgAsInt32(0));
      cout << "cam 5 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/6") {
      application->cameras.setColorMode(6 ,m.getArgAsInt32(0));
      cout << "cam 6 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/7") {
      application->cameras.setColorMode(7 ,m.getArgAsInt32(0));
      cout << "cam 7 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/8") {
      application->cameras.setColorMode(8 ,m.getArgAsInt32(0));
      cout << "cam 8 color " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/scene") {
      application->setScene(m.getArgAsInt32(0));
    }
  }
}
