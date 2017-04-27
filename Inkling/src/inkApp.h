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

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFlowTools.h"
#include "inkGameObject.h"
#include "inkGameObjectFactory.h"
#include "inkLevelController.h"
#include "inkLiveTester.h"

#if (TARGET_OS_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE) || (TARGET_IOS)
#include "ofxiOS.h"
#endif

#define USE_PROGRAMMABLE_GL

namespace ink
{

enum DrawMode
{
	DRAW_COMPOSITE = 0,
	DRAW_FLUID_DENSITY,
	DRAW_PARTICLES,
	DRAW_VELDOTS,
	DRAW_FLUID_FIELDS,
	DRAW_FLUID_VELOCITY,
	DRAW_FLUID_PRESSURE,
	DRAW_FLUID_TEMPERATURE,
	DRAW_FLUID_DIVERGENCE,
	DRAW_FLUID_VORTICITY,
	DRAW_FLUID_BUOYANCY,
	DRAW_FLUID_OBSTACLE,
	DRAW_FLOW_MASK,
	DRAW_OPTICAL_FLOW,
	DRAW_SOURCE,
	DRAW_MOUSE
};

enum GameState
{
	START
,	GAME
,	END
,	FLOW
,   NO_GAME_STATE
};

enum InkwellColor
{
  RED
, GREEN
, BLUE
, NO_COLOR
};

#if (TARGET_OS_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE) || (TARGET_IOS)
class inkApp : public ofxiOSApp
#else
class inkApp : public ofBaseApp
#endif
{

public:
	void setup();
	void update();
	void draw();

	// Camera
	ofVideoGrabber					simpleCam;
	bool							didCamUpdate;
	flowTools::ftFbo				cameraFbo;
	ofParameter<bool>				doFlipCamera;

	// Time
	float							lastTime;
	float							deltaTime;

	// Game
	GameState						gameState;
	int								score;
	shared_ptr<inkGameObject>		player;
	std::vector< shared_ptr
				 < inkGameObject> >	bullets;
	std::vector< shared_ptr
				 < inkGameObject> > enemies;
	std::vector< shared_ptr
				 < inkGameObject> > bonuses;
	std::vector< shared_ptr
				 < inkGameObject> > inkwells;

	shared_ptr<inkGameObject>		redInkwell;
	shared_ptr<inkGameObject>		greenInkwell;
	shared_ptr<inkGameObject>		blueInkwell;

	InkwellColor					inkColor;

	inkGameObjectFactory			gameObjectFactory;
	ofImage							playerImage;
	ofImage							enemyImage;
	ofImage							playerBulletImage;
	ofImage							enemyBulletImage;
	ofImage							lifeImage;
	ofImage							butterflyImage;
	ofImage							butterflyLineImage;
	ofImage							splashHDImage;
	ofImage							splashiPadImage;
	ofImage							redButtonImage;
	ofImage							greenButtonImage;
	ofImage							blueButtonImage;

	ofImage							startScreen;
	ofImage							endScreen;
	ofTrueTypeFont					scoreFont;

	float							maxEnemyAmplitude;
	float							maxEnemyShootInterval;
	int								lives;
    bool                            ignoreDoubleTouch;

	inkLevelController				levelController;
	inkLiveTester					liveTester;

	// FlowTools
	int								flowWidth;
	int								flowHeight;
	int								drawWidth;
	int								drawHeight;

	flowTools::ftOpticalFlow		opticalFlow;
	flowTools::ftVelocityMask		velocityMask;
	flowTools::ftFluidSimulation	fluidSimulation;
	flowTools::ftParticleFlow		particleFlow;

	flowTools::ftVelocitySpheres	velocityDots;

	ofImage							flowToolsLogoImage;
	bool							showLogo;
	int								resetTimerHack;

	// InputDraw
	flowTools::ftDrawInputForces	inputForces;

	void							touchDoubleTap( ofTouchEventArgs & touch );

	// Visualisations
	ofParameterGroup				visualizeParameters;
	flowTools::ftDisplayScalar		displayScalar;
	flowTools::ftVelocityField		velocityField;
	flowTools::ftTemperatureField	temperatureField;
	flowTools::ftPressureField		pressureField;
	flowTools::ftVTField			velocityTemperatureField;

	ofParameter<bool>				showScalar;
	ofParameter<bool>				showField;
	ofParameter<float>				displayScalarScale;
	void							setDisplayScalarScale( float& _value )
									{
										displayScalar.setScale( _value );
									}

	ofParameter<float>				velocityFieldScale;
	void							setVelocityFieldScale( float& _value )
									{
										velocityField.setVelocityScale( _value );
										velocityTemperatureField.setVelocityScale( _value );
									}

	ofParameter<float>				temperatureFieldScale;
	void							setTemperatureFieldScale( float& _value )
									{
										temperatureField.setTemperatureScale( _value ); 
										velocityTemperatureField.setTemperatureScale( _value );
									}

	ofParameter<float>				pressureFieldScale;
	void							setPressureFieldScale( float& _value )
									{
										pressureField.setPressureScale( _value );
									}

	ofParameter<bool>				velocityLineSmooth;
	void							setVelocityLineSmooth( bool& _value )
									{
										velocityField.setLineSmooth( _value ); 
										velocityTemperatureField.setLineSmooth( _value );
									}

	void							redButtonPressed();
	void							greenButtonPressed();
	void							blueButtonPressed();

	float							inkStartTime;
	float							inkIntervalTime;

	// GUI
	ofxPanel						settingsPanel;
	ofxPanel						buttonsPanel;
	ofxButton						redButton;
	ofxButton						greenButton;
	ofxButton						blueButton;
	void							setupGui();
	void							keyPressed( int key );
	void							drawGui();
	ofParameter<bool>				toggleGuiDraw;
	ofParameter<float>				guiFPS;
	ofParameter<float>				guiMinFPS;
	deque<float>					deltaTimeDeque;
	ofParameter<bool>				doFullScreen;
	void							setFullScreen( bool& _value ) {ofSetFullscreen( _value );}

	// DRAW
	ofParameter<bool>				doDrawCamBackground;

	ofParameter<int>				drawMode;
	void							drawModeSetName( int& _value );
	ofParameter<string>				drawName;

	void							drawComposite()
									{
										drawComposite
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawComposite( int _x, int _y, int _width, int _height );

	void							drawParticles()
									{
										drawParticles
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawParticles( int _x, int _y, int _width, int _height );

	void							drawFluidFields()
									{
										drawFluidFields
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawFluidFields( int _x, int _y, int _width, int _height );

	void							drawFluidDensity()
									{
										drawFluidDensity
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawFluidDensity( int _x, int _y, int _width, int _height );

	void							drawFluidVelocity()
									{
										drawFluidVelocity
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawFluidVelocity( int _x, int _y, int _width, int _height );

	void							drawFluidPressure()
									{
										drawFluidPressure
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawFluidPressure( int _x, int _y, int _width, int _height );

	void							drawFluidTemperature()
									{
										drawFluidTemperature
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawFluidTemperature( int _x, int _y, int _width, int _height );

	void							drawFluidDivergence()
									{
										drawFluidDivergence
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawFluidDivergence( int _x, int _y, int _width, int _height );

	void							drawFluidVorticity()
									{
										drawFluidVorticity
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawFluidVorticity( int _x, int _y, int _width, int _height );

	void							drawFluidBuoyance()
									{
										drawFluidBuoyance
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawFluidBuoyance( int _x, int _y, int _width, int _height );

	void							drawFluidObstacle()
									{
										drawFluidObstacle
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawFluidObstacle( int _x, int _y, int _width, int _height );

	void							drawMask()
									{
										drawMask
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawMask( int _x, int _y, int _width, int _height );

	void							drawOpticalFlow()
									{
										drawOpticalFlow
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawOpticalFlow( int _x, int _y, int _width, int _height );

	void							drawSource()
									{
										drawSource
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawSource( int _x, int _y, int _width, int _height );

	void							drawMouseForces()
									{
										drawMouseForces
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawMouseForces( int _x, int _y, int _width, int _height );

	void							drawVelocityDots()
									{
										drawVelocityDots
										( 0
										  , 0
										  , ofGetWindowWidth()
										  , ofGetWindowHeight()
										);
									}

	void							drawVelocityDots( int _x, int _y, int _width, int _height );

	//void							keyPressed(int key);
	void							keyReleased( int key );
	void							touchMoved( int x, int y, int id );
	void							mouseMoved( int x, int y );
	void							mouseDragged( int x, int y, int button );
	void							mousePressed( int x, int y, int button );
	void							mouseReleased( int x, int y, int button );
	void							mouseEntered( int x, int y );
	void							mouseExited( int x, int y );
	void							windowResized( int w, int h );
	void							dragEvent( ofDragInfo dragInfo );
	void							gotMessage( ofMessage msg );

};	//	inkApp

}	//	ink
