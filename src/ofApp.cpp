#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    if (args.size() >= 1) {
        fileName = args[0];
    } else {
        fileName = "arrangement";
    }

    
    if (args.size() >= 2) {
        ofSetDataPathRoot(args[1]);
    } else {
        ofSetDataPathRoot(DATA_DIR);
    }
    
    ofSetWindowPosition(0, 0);
    ofSetWindowShape(1920, 1080);
    ofSetFrameRate(FPS);
    
    vidSrc.loadMovie((string)"original/" + fileName + ".mov");
    
    if (!vidSrc.isLoaded()) {
        ofExit();
    }
    
    width = vidSrc.width;
    height = vidSrc.height;
    
    gray.allocate(width, height);
    
    
    // setup gui
    gui = new ofxUISuperCanvas("PetalArrangement");
    
    
    gui->setTheme(OFX_UI_THEME_BERLIN);
    gui->loadSettings("gui_petal-arrangement.xml");
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (vidSrc.getCurrentFrame() >= vidSrc.getTotalNumFrames()) {
        if (IS_PREVIEW)
            vidSrc.setFrame(0);
        else
            ofExit();
    }
    
    
    // get start point list
    pixels = vidSrc.getPixelsRef().getChannel(1);
    gray.setFromPixels(pixels.getPixels(), width, height);
    contourFinder.findContours(gray, 0, 16, 100, false);
    
    startPoints.clear();
    for (auto& blob : contourFinder.blobs) {
        startPoints.push_back( blob.centroid );
    }
    
    
    
    // get contour
    pixels = vidSrc.getPixelsRef().getChannel(0);
    gray.setFromPixels(pixels.getPixels(), width, height);
    contourFinder.findContours(gray, 1, width * height, 10, true);
    
    // draw
    ofBackground(16);
    
    ofSetColor(255);
    gray.draw(0, 0);
    contourFinder.draw();
    
    for (auto& blob : contourFinder.blobs) {
        
        ofPolyline poly;
        poly.setClosed(true);
        poly.addVertices(blob.pts);
        
        //poly.simplify(5);
        
        ofNoFill();
        ofSetColor(0, 0, 255);
        ofSetLineWidth(1);
        poly.draw();
        
        float perimeter = poly.getPerimeter();
        
        for (auto& startPt : startPoints) {
            
            unsigned int *closestIdx;
            ofPoint closestPt = poly.getClosestPoint(startPt, closestIdx);
            
            
            
            /*
            unsigned int idxPrev, idxNext;
            float lenToPrev, lenToNext;
            int cntVertices = poly.getVertices().size();
            
            idxPrev = (*closestIdx > 0) ? *closestIdx - 1 : cntVertices - 1;
            lenToPrev = (startPt - poly.getPointAtIndexInterpolated(idxPrev)).length();
            
            idxNext = (*closestIdx < cntVertices - 1) ? *closestIdx + 1 : 0;
            lenToNext = (startPt - poly.getPointAtIndexInterpolated(idxNext)).length();
            
            
            if (lenToPrev < lenToNext) {
                setStartPoint(poly, startPt, <#unsigned int startIdx#>)
            }*/
            
        }
        
        ofFill();
        ofSetColor(255, 0, 0);
        
        for (int l = 0; l < perimeter; l += 30) {
            ofCircle(poly.getPointAtLength(l), 5);
        }
    }
    
    
    
    
    
    ofSetColor(0, 255, 0);
    for (auto& pt: startPoints) {
        ofCircle(pt, 5);
    }
    
    
    // for next frame
    vidSrc.nextFrame();
    
}

//--------------------------------------------------------------
void ofApp::setStartPoint(ofPolyline *poly, ofPoint firstPt, unsigned int startIdx) {
    
    int cntVertices = poly->getVertices().size();
    vector<ofPoint> oldVertices;
    vector<ofPoint> newVertices;
    
    oldVertices = poly->getVertices();
    newVertices.push_back(firstPt);
    
    for (int i = 0; i < cntVertices; i++) {
        
        int idx = (startIdx + i) % cntVertices;
        
        newVertices.push_back( oldVertices[idx] );
    }
    
    poly->clear();
    poly->addVertices(newVertices);
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    if (gui) {
        gui->saveSettings("gui_petal-arrangement.xml");
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
