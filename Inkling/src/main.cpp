#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofGLFWWindowSettings windowSettings;

#ifdef USE_PROGRAMMABLE_GL
	windowSettings.setGLVersion(4, 1);
#endif
	windowSettings.width = 1280;
	windowSettings.height = 720;
	windowSettings.windowMode = OF_WINDOW;

	ofCreateWindow(windowSettings);

	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context (default method not using flowtools)

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
