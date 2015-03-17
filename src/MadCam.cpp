#include "MadCam.h"

//--------------------------------------------------------------
void MadCam::setup(){
  ofSetVerticalSync(true);
  parseConfig();
  midiHandler.registerHost(this);
  oscHandler.registerHost(this);
  cameras.setup();
}

//--------------------------------------------------------------
void MadCam::update(){
  ofBackground(0,0,0);
  oscHandler.process();
  cameras.update();
}

void
MadCam::setScene(int idx)
{
  cout << "SET SCENE index: " << idx << " num scenes: " << config.sceneMap.size() << endl;
  if(idx < 0 || idx >= config.sceneMap.size()) return;

  cout << "SET SCENE layout: " << config.sceneMap.at(idx).layout << endl;
  cout << "SET SCENE viewMode: " << config.sceneMap.at(idx).viewMode << endl;

  cameras.setLayout(config.sceneMap.at(idx).layout);
  cameras.setViewMode(config.sceneMap.at(idx).viewMode);

  cameras.setTriggerMode(config.sceneMap.at(idx).triggerMode);
  cameras.setColorMode(config.sceneMap.at(idx).fx);
  cameras.setFxAmount(config.sceneMap.at(idx).amountX, config.sceneMap.at(idx).amountY);

  for (uint i = 0; i < config.sceneMap.at(idx).slots.size(); i++) {
    cameras.setSlot(i, config.sceneMap.at(idx).slots.at(i));
  }
}

//--------------------------------------------------------------
void MadCam::draw(){
  cameras.draw();
  // ofDrawBitmapString(ofGetFrameRate(),20,20);
}

//--------------------------------------------------------------
void
MadCam::windowResized(int w, int h)
{
  cameras.setDimensions(w, h);
}

//--------------------------------------------------------------
void MadCam::exit() {
  // clean up
  midiHandler.close();
}


//--------------------------------------------------------------
void MadCam::keyPressed(int key){
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

  vector<tuple<int,int>> noteMap;
  vector<Scene> sceneMap;

  // MIDI SETUP
  XML.pushTag("settings",0);
  XML.pushTag("midi",0);

  uint numMappingTags = XML.getNumTags("mapping");

  if(numMappingTags > 0) {
    for(uint i = 0; i < numMappingTags; i++) {
      int note = XML.getValue("mapping:note",0,i);
      int cam  = XML.getValue("mapping:camera",0,i);
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

  config = { noteMap, sceneMap };
}

void MadCam::dragEvent(ofDragInfo dragInfo){}
void MadCam::keyReleased(int key){}
void MadCam::mouseMoved(int x, int y ){}
void MadCam::mouseDragged(int x, int y, int button){}
void MadCam::mousePressed(int x, int y, int button){}
void MadCam::mouseReleased(int x, int y, int button){}
void MadCam::gotMessage(ofMessage msg) {}

