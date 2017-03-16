// ================================================================================================
// Inkling is a game of wonder, where a fluid world emerges from your own designs.
//
// Copyright (C) 2017 Ledge Foundation Limited
//
// This program is free software; you can redistribute it and/or modify it under the terms of the 
// GNU General Public License as published by the Free Software Foundation; either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
// the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program; if 
// not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
// 02110-1301  USA
// ================================================================================================

#include "ofMain.h"
#include "ofApp.h"

int main()
{

	ofGLFWWindowSettings windowSettings;

#ifdef USE_PROGRAMMABLE_GL
	windowSettings.setGLVersion( 4, 1 );
#endif
	windowSettings.width = 1024;
	windowSettings.height = 768;
	windowSettings.windowMode = OF_WINDOW;

	ofCreateWindow( windowSettings );

	// vvvv setup the GL context (default method not using flowtools) vvvv
	//ofSetupOpenGL(1024,768,OF_WINDOW);			

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp() );

}
