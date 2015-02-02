#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxOpenCv.h"


#define FPS         24
#define IS_PREVIEW  true


#define DATA_DIR "/Volumes/MugiRAID1/Works/2015/01_fasciation/of/"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void setStartPoint(ofPolyline *poly, ofPoint firstPt, unsigned int startIdx);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    vector<string>          args;
    string                  fileName;
    int                     width, height;

    ofVideoPlayer           vidSrc;
    
    vector<ofPoint>         startPoints;

    // opencv
    ofPixels_<unsigned char> pixels;
    ofxCvColorImage         color;
    ofxCvGrayscaleImage     gray;
    ofxCvContourFinder      contourFinder;
    
    
    // gui
    ofxUISuperCanvas        *gui;

    
};
