#include "MadCam.h"

//--------------------------------------------------------------
void MadCam::setup(){
  ofSetVerticalSync(true);
  receiver.setup(8080);
  setupMidi();
  cams.setup();
}

//--------------------------------------------------------------
void MadCam::update(){
  ofBackground(0,0,0);

  while(receiver.hasWaitingMessages()) {
    ofxOscMessage m;
    receiver.getNextMessage(&m);

    string addr = m.getAddress();

    if(addr == "/trigger/state") {
      if(m.getArgAsInt32(0) % 2 == 0) {
        cams.setTriggerMode(false);
        cout << "trigger mode off" << endl;
      } else {
        cams.setTriggerMode(true);
        cout << "trigger mode on" << endl;
      }
    }

    if(addr == "/trigger") {
      cams.trigger(m.getArgAsInt32(0));
      cout << "trigger cam: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/layout") {
      switch(m.getArgAsInt32(0)) {
        case 0:
          cams.setArrangement(SINGLE);
          break;
        case 1:
          cams.setArrangement(DUAL_HORIZ);
          break;
        case 2:
          cams.setArrangement(TRIPLE_HORIZ);
          break;
        case 3:
          cams.setArrangement(TILED);
          break;
        case 4:
          cams.setArrangement(MONOCLE);
          break;
      }
      cout << "layout: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/decay") {
      cams.setDecay(m.getArgAsInt32(0));
      cout << "decay: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/global") {
      cams.setFxAmount(m.getArgAsInt32(0));
      cout << "global fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/0") {
      cams.setFxAmount(0 ,m.getArgAsInt32(0));
      cout << "cam 0 fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/1") {
      cams.setFxAmount(1 ,m.getArgAsInt32(0));
      cout << "cam 1 fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/2") {
      cams.setFxAmount(2 ,m.getArgAsInt32(0));
      cout << "cam 2 fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/3") {
      cams.setFxAmount(3 ,m.getArgAsInt32(0));
      cout << "cam 3 fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/4") {
      cams.setFxAmount(4 ,m.getArgAsInt32(0));
      cout << "cam 4 fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/5") {
      cams.setFxAmount(5 ,m.getArgAsInt32(0));
      cout << "cam 5 fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/6") {
      cams.setFxAmount(6 ,m.getArgAsInt32(0));
      cout << "cam 6 fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/7") {
      cams.setFxAmount(7 ,m.getArgAsInt32(0));
      cout << "cam 7 fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/8") {
      cams.setFxAmount(8 ,m.getArgAsInt32(0));
      cout << "cam 8 fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/0") {
      cams.setSlot(0 ,m.getArgAsInt32(0));
      cout << "cam 0 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/1") {
      cams.setSlot(1 ,m.getArgAsInt32(0));
      cout << "cam 1 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/2") {
      cams.setSlot(2 ,m.getArgAsInt32(0));
      cout << "cam 2 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/3") {
      cams.setSlot(3 ,m.getArgAsInt32(0));
      cout << "cam 3 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/4") {
      cams.setSlot(4 ,m.getArgAsInt32(0));
      cout << "cam 4 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/5") {
      cams.setSlot(5 ,m.getArgAsInt32(0));
      cout << "cam 5 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/6") {
      cams.setSlot(6 ,m.getArgAsInt32(0));
      cout << "cam 6 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/7") {
      cams.setSlot(7 ,m.getArgAsInt32(0));
      cout << "cam 7 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/slot/8") {
      cams.setSlot(8 ,m.getArgAsInt32(0));
      cout << "cam 8 slot: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/0") {
      cams.setColorMode(0 ,m.getArgAsInt32(0));
      cout << "cam 0 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/1") {
      cams.setColorMode(1 ,m.getArgAsInt32(0));
      cout << "cam 1 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/2") {
      cams.setColorMode(2 ,m.getArgAsInt32(0));
      cout << "cam 2 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/3") {
      cams.setColorMode(3 ,m.getArgAsInt32(0));
      cout << "cam 3 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/4") {
      cams.setColorMode(4 ,m.getArgAsInt32(0));
      cout << "cam 4 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/5") {
      cams.setColorMode(5 ,m.getArgAsInt32(0));
      cout << "cam 5 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/6") {
      cams.setColorMode(6 ,m.getArgAsInt32(0));
      cout << "cam 6 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/7") {
      cams.setColorMode(7 ,m.getArgAsInt32(0));
      cout << "cam 7 color: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/color/8") {
      cams.setColorMode(8 ,m.getArgAsInt32(0));
      cout << "cam 8 color " << m.getArgAsInt32(0) << endl;
    }
  }

  cams.update();
}

//--------------------------------------------------------------
void MadCam::draw(){
  cams.draw();
  ofDrawBitmapString(ofGetFrameRate(),20,20);
}

//--------------------------------------------------------------
void
MadCam::windowResized(int w, int h)
{
  cams.setDimensions(w, h);
}

//--------------------------------------------------------------
void MadCam::exit() {
  // clean up
  midiIn.closePort();
  midiIn.removeListener(this);
}

// MIDI
void MadCam::setupMidi()
{
  midiIn.listPorts();

  vector<string> portList = midiIn.getPortList();

  for(int i = 0; i < portList.size(); i++) {
    if(portList.at(i).compare(0, 9, "FastTrack") == 0) {
      cout << "opening " << portList.at(i) << endl;
      midiIn.openPort(portList.at(i));
      midiIn.addListener(this);
      midiIn.setVerbose(true);
      return;
    }
  }

  if(XML.loadFile("settings.xml"))
    cout << "settings.xml loaded!" << endl;

  XML.pushTag("MIDI",0);

  int numInstrTags = XML.getNumTags("INSTR");

  cout << "num: " << numInstrTags << endl;

  if(numInstrTags > 0) {
    for(int i = 0; i < numInstrTags; i++) {
      int note = XML.getValue("INSTR:NOTE",0,i);
      int cam = XML.getValue("INSTR:CAMERA",0,i);
      cout << "note: " << note << " Camera: " << cam << endl;
      noteMap.push_back(make_tuple(note, cam));
     }
  }

  //midiIn.openPort(1);
  //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
  // don't ignore sysex, timing, & active sense messages,
  // these are ignored by default
  //midiIn.ignoreTypes(false, false, false);
}

void MadCam::newMidiMessage(ofxMidiMessage& msg)
{
  if(msg.channel != 9) return;

  switch(msg.status) {
    case MIDI_NOTE_ON:
      //if(msg.pitch < grabbers.size())
        //selected = msg.pitch;
      // cout << "pitch: " << msg.pitch << endl;

      switch(msg.pitch) {
        // LAYOUT
        case 0:
          cams.setArrangement(SINGLE);
          break;
        case 1:
          cams.setArrangement(DUAL_HORIZ);
          break;
        case 2:
          cams.setArrangement(TRIPLE_HORIZ);
          break;
        case 3:
          cams.setArrangement(TILED);
          break;
        case 4:
          cams.setArrangement(MONOCLE);
          break;

      }

      for(int i = 0; i < noteMap.size(); i++) {
        auto mapping = noteMap.at(i);
        if(msg.pitch == get<0>(mapping) &&
           get<1>(mapping) >= 0 && get<1>(mapping) < cams.getNumCameras())
          cams.trigger(std::get<1>(noteMap.at(i)));
      }

      break;
    case MIDI_CONTROL_CHANGE:
      //cout << "ctrl: " << msg.control << " value: " << msg.value << endl;

      // Amount for all Cams simultaneously
      if(msg.control == 1)
        cams.setFxAmount(msg.value);

      // Amount per cam
      if(msg.control > 1 && msg.control < 20)
        cams.setFxAmount(msg.control % 10, msg.value);

      // set camera in slot
      if(msg.control > 19 && msg.control < 30)
        cams.setSlot(msg.control - 20, msg.value);

      // set decay
      if(msg.control == 30)
        cams.setDecay(msg.value);

      // turn on trigger mode
      if(msg.control == 32) {
        if(msg.value < 64)
          cams.setTriggerMode(true);
        else
          cams.setTriggerMode(false);
      }

      // set camera in slot
      if(msg.control > 31 && msg.control < 41)
        cams.setColorMode(msg.control - 32, msg.value);

      break;
    default:
      break;
  }
}

//--------------------------------------------------------------
void MadCam::keyPressed(int key){
  int baseKey = 49;

  if(key == 117)
    cams.toggleTrigger();

  if(key == 257)
    cams.trigger(0);

  if(key == 258)
    cams.trigger(1);

  if(key == 259)
    cams.trigger(2);

  if(key == 260)
    cams.trigger(3);

  // if(key >= baseKey && key < (baseKey + cams.getNumCameras())) {
  //   cams.setSlot((key % baseKey) % cams.getNumCameras());
  //   return;
  // }

  switch(key) {
    case 113:
      cams.setArrangement(SINGLE);
      break;
    case 119:
      cams.setArrangement(DUAL_HORIZ);
      break;
    case 101:
      cams.setArrangement(TRIPLE_HORIZ);
      break;
    case 114:
      cams.setArrangement(TILED);
      break;
    case 116:
      cams.setArrangement(MONOCLE);
      break;
    case 99:
      cams.setViewMode((CROP));
      break;
    case 115:
      cams.setViewMode((SCALE));
      break;
    case 54:
      cams.setColorMode(0);
      break;
    case 55:
      cams.setColorMode(1);
      break;
    case 56:
      cams.setColorMode(2);
      break;
    case 57:
      cams.setColorMode(3);
      break;
    case 48:
      cams.setColorMode(4);
      break;
    case 45:
      cams.setColorMode(5);
      break;
  }
}

void MadCam::dragEvent(ofDragInfo dragInfo){}
void MadCam::keyReleased(int key){}
void MadCam::mouseMoved(int x, int y ){}
void MadCam::mouseDragged(int x, int y, int button){}
void MadCam::mousePressed(int x, int y, int button){}
void MadCam::mouseReleased(int x, int y, int button){}
void MadCam::gotMessage(ofMessage msg) {}
