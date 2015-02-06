#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    void setup_cams();
    void update_cams();
    void draw_cams();

    int calculate_width();

    ofVideoGrabber vidGrabber;
    vector<ofVideoGrabber> grabbers;

    int camWidth;
    int camHeight;
    int winWidth;
    int winHeight;
    int scaledWidth;

    int selected; 
};
