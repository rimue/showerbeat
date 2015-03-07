#pragma once

#include "ofMain.h"


class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setupArduino(const int & version);
//    void digitalPinChanged(const int & pinNum);
//    void analogPinChanged(const int & pinNum);
    void updateArduino();
    
    ofArduino ard;
	bool		bSetupArduino;			// flag variable for setting up arduino once
    
    
    ofSoundPlayer 		music;
    float 				* fftSmoothed;
    int nBandsToGet;
    int musicVal0 = 0;
    int musicVal1 = 0;
    int musicVal2 = 0;
    string digital;
    
    float * val;
};

