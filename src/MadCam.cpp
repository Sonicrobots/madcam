#include "MadCam.h"

//--------------------------------------------------------------
void MadCam::setup(){
  ofSetVerticalSync(true);

  frameCount = 0;
  feedback = false;
  currentCam = 0;

  parseConfig();
  midiHandler.registerHost(this);
  oscHandler.registerHost(this);
  cameras.setup(config.camMap);
  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
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
  if(idx < 0 || idx >= (int)config.sceneMap.size()) return;

  cameras.setLayout(config.sceneMap.at(idx).layout);
  cameras.setViewMode(config.sceneMap.at(idx).viewMode);

  cameras.setTriggerMode(config.sceneMap.at(idx).triggerMode);
  cameras.setColorMode(config.sceneMap.at(idx).fx);
  cameras.setFxAmount(config.sceneMap.at(idx).amountX, config.sceneMap.at(idx).amountY);

  for (uint i = 0; i < config.sceneMap.at(idx).slots.size(); i++)
    cameras.setSlot(i, config.sceneMap.at(idx).slots.at(i));

  setFeedback(config.sceneMap.at(idx).feedbackMode);
  setAlpha(config.sceneMap.at(idx).alpha);
  setIterations(config.sceneMap.at(idx).iterations);
  setXOffset(config.sceneMap.at(idx).xoffset);
  setYOffset(config.sceneMap.at(idx).yoffset);
}

void 
MadCam::setIterations(int iter)
{
  if(iter >= 0 && iter <= 30)
    iterations = iter;
}

void
MadCam::setAlpha(int al)
{
  if(al >= 0 && al <= 255)
    alpha = al;
}

void
MadCam::setXOffset(int off)
{
  if(off >= 0 && off <= ofGetWidth())
    xoffset = off;
}

void
MadCam::setYOffset(int off)
{
  if(off >= 0 && off <= ofGetWidth())
    yoffset = off;
}

void 
MadCam::setFeedback(bool mode)
{
  if(mode && feedback) return;

  // if(mode) {
  //    fbo.begin();
  //    ofClear(255,255,255,0);
  //    fbo.end();
  // }

  feedback = mode;
}

//--------------------------------------------------------------
void MadCam::draw(){
  if(feedback) {
    fbo.begin();
    ofClear(255,255,255,0);
    cameras.draw();
    fbo.end();
    for(int i = 0; i < iterations; i++) {
       fbo.begin();
       ofEnableAlphaBlending();
       ofSetColor(255,255,255,alpha);
       fbo.draw(ofRandom(-xoffset,xoffset),ofRandom(-yoffset,yoffset));
       ofDisableAlphaBlending();
       fbo.end();
    }
    fbo.draw(0,0);
  } else {
    fbo.begin();
    ofClear(255,255,255,0);
    fbo.end();
    cameras.draw();
  }
  frameCount++;
}

//--------------------------------------------------------------
void
MadCam::windowResized(int w, int h)
{
  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  cameras.setDimensions(w, h);
}

//--------------------------------------------------------------
void MadCam::exit() {
  midiHandler.close();
}


//--------------------------------------------------------------
void MadCam::keyPressed(int key){
  if(key == 358) {
    currentCam++;
    cameras.setSlot(0, currentCam);
  }

  if(key == 358) {
    currentCam = currentCam >= 0 ? currentCam - 1 : 0;
    cameras.setSlot(0, currentCam);
  }

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

  vector<tuple<string,int>> camMap;
  vector<tuple<int,int>> noteMap;
  vector<Scene> sceneMap;

  XML.pushTag("settings",0);
  
  // CAMERA SETUP
  XML.pushTag("cameras",0);

  uint numMappingTags = XML.getNumTags("mapping");

  if(numMappingTags > 0) {
    for(uint i = 0; i < numMappingTags; i++) {
      string path = XML.getValue("mapping:id","",i);
      int index = XML.getValue("mapping:index",0,i);
      camMap.push_back(make_tuple(path,index));
    }
  }

  XML.popTag();

  // MIDI SETUP
  XML.pushTag("midi",0);

  numMappingTags = XML.getNumTags("mapping");

  if(numMappingTags > 0) {
    for(uint i = 0; i < numMappingTags; i++) {
      int note = XML.getValue("mapping:note",0,i);
      int cam = XML.getValue("mapping:camera",0,i);
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

      bool feedback = static_cast<bool>(XML.getValue("scene:feedback-mode", 0, i));
      int alpha     = XML.getValue("scene:alpha", 0, i);
      int iter      = XML.getValue("scene:iterations", 0, i);
      int xoffset   = XML.getValue("scene:xoffset", 0, i);
      int yoffset   = XML.getValue("scene:yoffset", 0, i);

      XML.pushTag("scene", i);

      uint numSlotTags = XML.getNumTags("slot");
      vector<int> slots;

      if(numSlotTags > 0) {
        for (uint j = 0; j < numSlotTags; j++) {
          slots.push_back(XML.getValue("slot", 0, j));
        }
      }
      XML.popTag();

      sceneMap.push_back({ 
	layout, 
	mode, 
	trigger, 
	fx, 
	amountX, 
	amountY, 
	slots,
	feedback,
	alpha,
	xoffset,
	yoffset,
	iter
      });
    }
  }

  config = { camMap, noteMap, sceneMap };
}

void
MadCam::dumpSettings()
{
  cerr << "<snip>" << endl;

  cerr << "<feedback-mode>" << (feedback ? "1" : "0") << "</feedback-mode>" << endl;
  cerr << "<iterations>" << iterations << "</iterations>" << endl;
  cerr << "<alpha>" << alpha << "</alpha>" << endl;
  cerr << "<xoffset>" << xoffset << "</xoffset>" << endl;
  cerr << "<yoffset>" << yoffset << "</yoffset>" << endl;
  
  cerr << "</snip>" << endl;
}

void MadCam::mousePressed(int x, int y, int button) 
{ 
  dumpSettings();
}

void MadCam::dragEvent(ofDragInfo dragInfo){}
void MadCam::keyReleased(int key){}
void MadCam::mouseMoved(int x, int y ){}
void MadCam::mouseDragged(int x, int y, int button){}
void MadCam::mouseReleased(int x, int y, int button){}
void MadCam::gotMessage(ofMessage msg) {}

