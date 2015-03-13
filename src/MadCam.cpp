#include "MadCam.h"

//--------------------------------------------------------------
void MadCam::setup(){
  ofSetVerticalSync(true);
  parseConfig();
  setupMidi();
  //cameras.setup();

  oscHandler.registerHost(this);
}

//--------------------------------------------------------------
void MadCam::update(){
  ofBackground(0,0,0);
  oscHandler.process();
  // cameras.update();
}

void
MadCam::setScene(int idx)
{
  cout << "SET SCENE index: " << idx << " num scenes: " << sceneMap.size() << endl;
  if(idx < 0 || idx >= sceneMap.size()) return;

  cout << "SET SCENE layout: " << sceneMap.at(idx).layout << endl;
  cout << "SET SCENE viewMode: " << sceneMap.at(idx).viewMode << endl;

  // cameras.setLayout(sceneMap.at(idx).layout);
  // cameras.setViewMode(sceneMap.at(idx).viewMode);

  // cameras.setTriggerMode(sceneMap.at(idx).triggerMode);
  // cameras.setColorMode(sceneMap.at(idx).fx);
  // cameras.setFxAmount(sceneMap.at(idx).amountX, sceneMap.at(idx).amountY);

  // for (uint i = 0; i < sceneMap.at(idx).slots.size(); i++) {
  //   cameras.setSlot(i, sceneMap.at(idx).slots.at(i));
  // }
}

//--------------------------------------------------------------
void MadCam::draw(){
  // cameras.draw();
  ofDrawBitmapString(ofGetFrameRate(),20,20);
}

//--------------------------------------------------------------
void
MadCam::windowResized(int w, int h)
{
  // cameras.setDimensions(w, h);
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
            cameras.setLayout(SINGLE);
            break;
          case 1:
            cameras.setLayout(DUAL_HORIZ);
            break;
          case 2:
            cameras.setLayout(TRIPLE_HORIZ);
            break;
          case 3:
            cameras.setLayout(TILED);
            break;
          case 4:
            cameras.setLayout(MONOCLE);
            break;

        }

        for(int i = 0; i < noteMap.size(); i++) {
          auto mapping = noteMap.at(i);
          if(msg.pitch == get<0>(mapping) &&
             get<1>(mapping) >= 0 && get<1>(mapping) < cameras.getNumCameras())
            cameras.trigger(std::get<1>(noteMap.at(i)));
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
        cameras.setSlot(msg.control - 20, msg.value);

      // set decay
      if(msg.control == 30)
        cameras.setDecay(msg.value);

      // turn on trigger mode
      if(msg.control == 32) {
        if(msg.value < 64)
          cameras.setTriggerMode(true);
        else
          cameras.setTriggerMode(false);
      }

      // set camera in slot
      if(msg.control > 31 && msg.control < 41)
        cameras.setColorMode(msg.control - 32, msg.value);

    case MIDI_NOTE_OFF:
      break;
    case MIDI_PROGRAM_CHANGE:
      break;
    case MIDI_PITCH_BEND:
      break;
    case MIDI_AFTERTOUCH:
      break;
    case MIDI_POLY_AFTERTOUCH:
      break;
    case MIDI_SYSEX:
      break;
    case MIDI_TIME_CODE:
      break;
    case MIDI_SONG_POS_POINTER:
      break;
    case MIDI_SONG_SELECT:
      break;
    case MIDI_TUNE_REQUEST:
      break;
    case MIDI_SYSEX_END:
      break;
    case MIDI_TIME_CLOCK:
      break;
    case MIDI_START:
      break;
    case MIDI_CONTINUE:
      break;
    case MIDI_STOP:
      break;
    case MIDI_ACTIVE_SENSING:
      break;
    case MIDI_SYSTEM_RESET:
      break;
    default:
      break;
  }
}

//--------------------------------------------------------------
void MadCam::keyPressed(int key){
  int baseKey = 49;

  if(key == 117)
    cameras.reloadShaders();

  if(key == 257)
    cameras.trigger(0);

  if(key == 258)
    cameras.trigger(1);

  if(key == 259)
    cameras.trigger(2);

  if(key == 260)
    cameras.trigger(3);

  // if(key >= baseKey && key < (baseKey + cameras.getNumCameras())) {
  //   cameras.setSlot((key % baseKey) % cameras.getNumCameras());
  //   return;
  // }

  switch(key) {
    case 113:
      cameras.setLayout(SINGLE);
      break;
    case 119:
      cameras.setLayout(DUAL_HORIZ);
      break;
    case 101:
      cameras.setLayout(TRIPLE_HORIZ);
      break;
    case 114:
      cameras.setLayout(TILED);
      break;
    case 116:
      cameras.setLayout(MONOCLE);
      break;
    case 99:
      cameras.setViewMode((CROP));
      break;
    case 115:
      cameras.setViewMode((SCALE));
      break;
    case 54:
      cameras.setColorMode(0);
      break;
    case 55:
      cameras.setColorMode(1);
      break;
    case 56:
      cameras.setColorMode(2);
      break;
    case 57:
      cameras.setColorMode(3);
      break;
    case 48:
      cameras.setColorMode(4);
      break;
    case 45:
      cameras.setColorMode(5);
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

  uint numMappingTags = XML.getNumTags("mapping");

  if(numMappingTags > 0) {
    for(uint i = 0; i < numMappingTags; i++) {
      int note = XML.getValue("mapping:note",0,i);
      int cam  = XML.getValue("mapping:camera",0,i);
      //cout << "note: " << note << " Camera: " << cam << endl;
      noteMap.push_back(make_tuple(note, cam));
     }
  }

  XML.popTag();

  // SCENES
  XML.pushTag("scenes",0);

  uint numSceneTags = XML.getNumTags("scene");
  if(numSceneTags > 0) {
    for (uint i = 0; i < numSceneTags; i++) {
      Layout layout = static_cast<Layout>(XML.getValue("scene:layout", 0, i));
      ViewMode mode = static_cast<ViewMode>(XML.getValue("scene:view-mode", 0, i));
      bool trigger  = static_cast<bool>(XML.getValue("scene:trigger-mode", 0, i));
      int fx        = XML.getValue("scene:fx:type",     0, i);
      int amountX   = XML.getValue("scene:fx:amount-x", 0, i);
      int amountY   = XML.getValue("scene:fx:amount-y", 0, i);

      XML.pushTag("scene", i);

      uint numSlotTags = XML.getNumTags("slot");
      vector<int> slots;

      // cout << " num slots: " << numSlotTags << endl;

      if(numSlotTags > 0) {
        for (uint j = 0; j < numSlotTags; j++) {
          slots.push_back(XML.getValue("slot", 0, j));
          // cout << "slot at " << j << " is " << slots.at(j) << endl;
        }
      }
      XML.popTag();

      sceneMap.push_back({ layout, mode, trigger, fx, amountX, amountY, slots });
    }
  }

  for (uint i = 0; i < sceneMap.size(); i++) {
    // cout << "-------------" << endl;
    // cout << "layout: " << sceneMap.at(i).layout << endl;
    // cout << "view-mode: " << sceneMap.at(i).viewMode << endl;
    // cout << "trigger-mode" << sceneMap.at(i).triggerMode << endl;
    // cout << "fx" << sceneMap.at(i).fx << endl;
    // cout << "amountX " << sceneMap.at(i).amountX << endl;
    // cout << "amountY " << sceneMap.at(i).amountY << endl;
  }
}

void MadCam::dragEvent(ofDragInfo dragInfo){}
void MadCam::keyReleased(int key){}
void MadCam::mouseMoved(int x, int y ){}
void MadCam::mouseDragged(int x, int y, int button){}
void MadCam::mousePressed(int x, int y, int button){}
void MadCam::mouseReleased(int x, int y, int button){}
void MadCam::gotMessage(ofMessage msg) {}
