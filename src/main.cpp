#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings s;
    s.setGLVersion(3, 2);
    s.setSize(1024, 1024);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    
    ofCreateWindow(s);
    
	ofRunApp(new ofApp());

}
