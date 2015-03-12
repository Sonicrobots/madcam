#include "MadCam.h"

//--------------------------------------------------------------
void MadCam::setup(){
  ofSetVerticalSync(true);
  parseConfig();
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

    cout << "Message for address: " << addr << endl;

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
          cams.setLayout(SINGLE);
          break;
        case 1:
          cams.setLayout(DUAL_HORIZ);
          break;
        case 2:
          cams.setLayout(TRIPLE_HORIZ);
          break;
        case 3:
          cams.setLayout(TILED);
          break;
        case 4:
          cams.setLayout(MONOCLE);
          break;
      }
      cout << "layout: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/decay") {
      cams.setDecay(m.getArgAsInt32(0));
      cout << "decay: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/global") {
      cams.setFxAmount(m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "global fx amount: " << m.getArgAsInt32(0) << endl;
    }

    if(addr == "/fx/amount/0") {
      cams.setFxAmount(0 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 0 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/1") {
      cams.setFxAmount(1 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 1 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/2") {
      cams.setFxAmount(2 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 2 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/3") {
      cams.setFxAmount(3 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 3 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/4") {
      cams.setFxAmount(4 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 4 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/5") {
      cams.setFxAmount(5 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 5 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/6") {
      cams.setFxAmount(6 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 6 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/7") {
      cams.setFxAmount(7 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 7 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/fx/amount/8") {
      cams.setFxAmount(8 ,m.getArgAsInt32(0), m.getArgAsInt32(1));
      cout << "cam 8 fx x: " << m.getArgAsInt32(0) <<  " y: " << m.getArgAsInt32(1) << endl;
    }

    if(addr == "/slot/global") {
      cams.setSlot(m.getArgAsInt32(0));
      cout << "cam globa; slot: " << m.getArgAsInt32(0) << endl;
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

    if(addr == "/color/global") {
      cams.setColorMode(m.getArgAsInt32(0));
      cout << "cam 0 color: " << m.getArgAsInt32(0) << endl;
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

    if(addr == "/scene") {
      int idx = m.getArgAsInt32(0);
      if(idx >= 0 && idx < sceneMap.size()) setScene(idx);
    }
  }

  cams.update();
}

void
MadCam::setScene(int idx)
{
  cams.setLayout(sceneMap.at(idx).layout);
  cams.setViewMode(sceneMap.at(idx).viewMode);
  cams.setTriggerMode(sceneMap.at(idx).triggerMode);
  cams.setColorMode(sceneMap.at(idx).fx);
  cams.setFxAmount(sceneMap.at(idx).amountX, sceneMap.at(idx).amountY);
  for (uint i = 0; i < sceneMap.at(idx).slots.size(); i++) {
    cams.setSlot(i, sceneMap.at(idx).slots.at(i));
  }
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
      break;
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
  if(msg.channel == 2) {
    switch(msg.status) {
      case MIDI_NOTE_ON:
        //if(msg.pitch < grabbers.size())
          //selected = msg.pitch;
        // cout << "pitch: " << msg.pitch << endl;

        switch(msg.pitch) {
          // LAYOUT
          case 0:
            cams.setLayout(SINGLE);
            break;
          case 1:
            cams.setLayout(DUAL_HORIZ);
            break;
          case 2:
            cams.setLayout(TRIPLE_HORIZ);
            break;
          case 3:
            cams.setLayout(TILED);
            break;
          case 4:
            cams.setLayout(MONOCLE);
            break;

        }

        for(int i = 0; i < noteMap.size(); i++) {
          auto mapping = noteMap.at(i);
          if(msg.pitch == get<0>(mapping) &&
             get<1>(mapping) >= 0 && get<1>(mapping) < cams.getNumCameras())
            cams.trigger(std::get<1>(noteMap.at(i)));
        }

        break;
    }
  }

  if(msg.channel != 9) return;

  switch(msg.status) {
    case MIDI_CONTROL_CHANGE:
      //cout << "ctrl: " << msg.control << " value: " << msg.value << endl;

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
    cams.reloadShaders();

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
      cams.setLayout(SINGLE);
      break;
    case 119:
      cams.setLayout(DUAL_HORIZ);
      break;
    case 101:
      cams.setLayout(TRIPLE_HORIZ);
      break;
    case 114:
      cams.setLayout(TILED);
      break;
    case 116:
      cams.setLayout(MONOCLE);
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

void
MadCam::parseConfig()
{
  if(XML.loadFile("settings.xml"))
    cout << "settings.xml loaded!" << endl;
  else
    cout << "settings.xml NOT loaded!" << endl;

  // MIDI SETUP
  XML.pushTag("settings",0);
  XML.pushTag("midi",0);

  int numMappingTags = XML.getNumTags("mapping");

  if(numMappingTags > 0) {
    for(uint i = 0; i < numMappingTags; i++) {
      int note = XML.getValue("mapping:note",0,i);
      int cam  = XML.getValue("mapping:camera",0,i);
      cout << "note: " << note << " Camera: " << cam << endl;
      noteMap.push_back(make_tuple(note, cam));
     }
  }

  XML.popTag();

  // SCENES
  XML.pushTag("scenes",0);

  int numSceneTags = XML.getNumTags("scene");
  if(numSceneTags > 0) {
    for (uint i = 0; i < numSceneTags; i++) {
      Layout layout = static_cast<Layout>(XML.getValue("scene:layout", 0, i));
      ViewMode mode = static_cast<ViewMode>(XML.getValue("scene:view-mode", 0, i));
      bool trigger  = static_cast<bool>(XML.getValue("scene:trigger-mode", 0, i));
      int fx        = XML.getValue("scene:fx:type",     0, i);
      int amountX   = XML.getValue("scene:fx:amount-x", 0, i);
      int amountY   = XML.getValue("scene:fx:amount-y", 0, i);


      XML.pushTag("scene", i);
      int numSlotTags = XML.getNumTags("slot");
      vector<int> slots;

      cout << " num slots: " << numSlotTags << endl;

      if(numSlotTags > 0) {
        for (uint j = 0; j < numSlotTags; j++) {
          slots.push_back(XML.getValue("slot", 0, j));
          cout << "slot at " << j << " is " << slots.at(j) << endl;
        }
      }
      XML.popTag();

      sceneMap.push_back({ layout, mode, trigger, fx, amountX, amountY, slots });
    }
  }

  for (uint i = 0; i < sceneMap.size(); i++) {
    cout << "-------------" << endl;
    cout << "layout: " << sceneMap.at(i).layout << endl;
    cout << "view-mode: " << sceneMap.at(i).viewMode << endl;
    cout << "trigger-mode" << sceneMap.at(i).triggerMode << endl;
    cout << "fx" << sceneMap.at(i).fx << endl;
    cout << "amountX " << sceneMap.at(i).amountX << endl;
    cout << "amountY " << sceneMap.at(i).amountY << endl;
  }
}

void MadCam::dragEvent(ofDragInfo dragInfo){}
void MadCam::keyReleased(int key){}
void MadCam::mouseMoved(int x, int y ){}
void MadCam::mouseDragged(int x, int y, int button){}
void MadCam::mousePressed(int x, int y, int button){}
void MadCam::mouseReleased(int x, int y, int button){}
void MadCam::gotMessage(ofMessage msg) {}
