#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ard.connect("/dev/tty.usbmodem1421", 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;
    
    // the fft needs to be smoothed out, so we create an array of floats. for that purpose:
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    
//    nBandsToGet = 100;
    nBandsToGet = 2;
}


//--------------------------------------------------------------
void ofApp::update(){
    
    updateArduino();
    
    // update the sound playing system:
    ofSoundUpdate();
    
    
    // (5) grab the fft, and put in into a "smoothed" array,
    //		by taking maximums, as peaks and then smoothing downward
    val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
    
    
    
    for (int i = 0;i < nBandsToGet; i++){
        
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.96f;
        
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
//        musicVal0 = int(ofMap(val[30], 0, 0.7, 0, 230));
//        musicVal2 = int(ofMap(val[33], 0, 1, 0, 255));
        
        musicVal0 = int(ofMap(val[0], 0, 1, 0, 255));
        musicVal1 = int(ofMap(val[1], 0, 1, 0, 255));
        musicVal2 = int(ofMap(val[2], 0, 1, 0, 255));

    }
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version){
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // set pin D11 as PWM (analog output)
    ard.sendDigitalPinMode(9, ARD_PWM);
    ard.sendDigitalPinMode(10, ARD_PWM);
    // set pin D13 as digital output
    ard.sendDigitalPinMode(12, ARD_OUTPUT);

}
//--------------------------------------------------------------
void ofApp::updateArduino(){
    ard.update();
    if (bSetupArduino) {
        
        ard.sendPwm(9, musicVal0);
        ard.sendPwm(10, musicVal1);
    
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw the fft resutls:
    ofSetColor(255,255,255,255);
    
    float width = (float)(5*128) / nBandsToGet;
    for (int i = 0;i < nBandsToGet; i++){
        // (we use negative height here, because we want to flip them
        // because the top corner is 0,0)
        ofRect(50+i*width, 250, width,-(fftSmoothed[i] * 200));
    }

    
        if (musicVal1 > 1) {
            ard.sendDigital(12, ARD_HIGH);
            digital = "ON";
        }else{
            ard.sendDigital(12, ARD_LOW);
            digital = "OFF";
        }

    ofSetColor(0);

    ofDrawBitmapString("BandWidth: "+ofToString(nBandsToGet), 50, 300);

    ofDrawBitmapString("AnalogOutPin 9", 50, 330);
    //ofDrawBitmapString("Spectrum Val(3): " + ofToString(val[3]), 70, 330);
    ofDrawBitmapString("Mapped Val: "+ofToString(musicVal0), 70, 345);
    
    ofDrawBitmapString("DigitalOutPin 13", 50, 375);
    //ofDrawBitmapString("Spectrum Val(33): "+ofToString(val[33]), 70, 375);
    ofDrawBitmapString("Mapped Val: "+digital, 70, 390);
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    if (key == 'w') {
        music.loadSound("Wakemeup.mp3");
        music.play();
    }
    if (key == 'p') {
        music.loadSound("Phonecall.mp3");
        music.play();
    }
    if (key == 'q') {
        music.loadSound("queen.mp3");
        music.play();
    }
    if (key == 'i') {
        music.loadSound("ifeelgood.mp3");
        music.play();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    	ard.sendDigital(13, ARD_HIGH);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    	ard.sendDigital(13, ARD_LOW);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

