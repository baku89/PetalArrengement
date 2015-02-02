#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char *argv[] ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    
    vector<string> args;
    
    for (int i = 0; i < argc - 1; i++) {
        if (ofToString(argv[i]) == "--arguments") {
            for (i++; i < argc; i++) {
                args.push_back(ofToString(argv[i]));
            }
        }
    }
    
    ofApp *app = new ofApp();
    app->args = args;
    
	ofRunApp(app);

}
