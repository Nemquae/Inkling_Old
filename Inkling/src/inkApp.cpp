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

#include "inkApp.h"
#include "inkOffenseComponent.h"

using namespace ink;
using namespace flowTools;

//-------------------------------------------------------------------------------------------------
void inkApp::setup()
{
	player = gameObjectFactory.create( PLAYER );

	gameState = FLOW;
	score = 0;
	lives = 0;

	playerImage.loadImage( "player.png" );
	enemyImage.loadImage( "enemy0.png" );
	playerBulletImage.loadImage( "player_bullet.png" );
	enemyBulletImage.loadImage( "enemy_bullet.png" );
	lifeImage.loadImage( "life_image.png" );

	player->get<inkSpriteComponent>()->img = make_shared<ofImage>(playerImage);

	maxEnemyAmplitude = 3.0;
	maxEnemyShootInterval = 1.5;

	ofSetVerticalSync( false );
	ofSetLogLevel( OF_LOG_NOTICE );
	//ofSetBackgroundAuto(true);
	//ofSetBackgroundColor(ofColor(255,255,255,127));

	drawWidth = 1280;
	drawHeight = 720;
	// process all but the density on 16th resolution
	flowWidth = drawWidth / 4;
	flowHeight = drawHeight / 4;
    
    ofLogNotice(string("GLSL Version = ") + string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION)) + string("\n"));

	// FLOW & MASK
	opticalFlow.setup( flowWidth, flowHeight );
	velocityMask.setup( drawWidth, drawHeight );

	// FLUID & PARTICLES
	fluidSimulation.setup( flowWidth, flowHeight, drawWidth, drawHeight );
	particleFlow.setup( flowWidth, flowHeight, drawWidth, drawHeight );

	flowToolsLogoImage.load( "inkling.png" );
	fluidSimulation.addObstacle( flowToolsLogoImage.getTexture() );
	showLogo = false;

	velocityDots.setup( flowWidth / 4, flowHeight / 4 );

	// VISUALIZATION
	displayScalar.setup( flowWidth, flowHeight );
	velocityField.setup( flowWidth / 4, flowHeight / 4 );
	temperatureField.setup( flowWidth / 4, flowHeight / 4 );
	pressureField.setup( flowWidth / 4, flowHeight / 4 );
	velocityTemperatureField.setup( flowWidth / 4, flowHeight / 4 );

	// MOUSE & TOUCH DRAW
	inputForces.setup( flowWidth, flowHeight, drawWidth, drawHeight );

	// CAMERA
	//simpleCam.setup(640, 480, true);
	//didCamUpdate = true;
	//cameraFbo.allocate(640, 480);
	//cameraFbo.black();

	ofAddListener( ofEvents().touchDoubleTap, this, &inkApp::touchDoubleTap );

	// GUI
	setupGui();

	//mouseForces.invertForce(0);
	//mouseForces.invertForce(3);

	lastTime = ofGetElapsedTimef();

}

void inkApp::touchDoubleTap( ofTouchEventArgs & touch )
{
	toggleGuiDraw = !toggleGuiDraw;
}

//-------------------------------------------------------------------------------------------------
void inkApp::setupGui()
{

	gui.setup( "settings" );
	gui.setDefaultBackgroundColor( ofColor( 0, 0, 0, 127 ) );
	gui.setDefaultFillColor( ofColor( 160, 160, 160, 160 ) );
	gui.add( guiFPS.set( "average FPS", 0, 0, 60 ) );
	gui.add( guiMinFPS.set( "minimum FPS", 0, 0, 60 ) );
	gui.add( doFullScreen.set( "fullscreen (F)", false ) );
	doFullScreen.addListener( this, &inkApp::setFullScreen );
	gui.add( toggleGuiDraw.set( "show gui (G)", false ) );
	gui.add( doFlipCamera.set( "flip camera", true ) );
	gui.add( doDrawCamBackground.set( "draw camera (C)", false ) );

	gui.add( drawMode.set( "draw mode"
						   , DRAW_FLUID_DENSITY
						   , DRAW_FLUID_DENSITY
						   , DRAW_MOUSE
	)
	);

	drawMode.addListener( this, &inkApp::drawModeSetName );
	gui.add( drawName.set( "MODE", "draw name" ) );


	int guiColorSwitch = 0;
	ofColor guiHeaderColor[ 2 ];
	guiHeaderColor[ 0 ].set( 160, 160, 80, 200 );
	guiHeaderColor[ 1 ].set( 80, 160, 160, 200 );
	ofColor guiFillColor[ 2 ];
	guiFillColor[ 0 ].set( 160, 160, 80, 200 );
	guiFillColor[ 1 ].set( 80, 160, 160, 200 );

	gui.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	gui.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	gui.add( opticalFlow.parameters );

	gui.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	gui.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	gui.add( velocityMask.parameters );

	gui.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	gui.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	gui.add( fluidSimulation.parameters );

	gui.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	gui.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	gui.add( particleFlow.parameters );

	gui.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	gui.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	gui.add( inputForces.leftButtonParameters );

	gui.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	gui.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	gui.add( inputForces.rightButtonParameters );

	gui.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	gui.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	gui.add( inputForces.middleButtonParameters );

	visualizeParameters.setName( "visualizers" );
	visualizeParameters.add( showScalar.set( "show scalar", true ) );
	visualizeParameters.add( showField.set( "show field", true ) );
	visualizeParameters.add( displayScalarScale.set( "scalar scale", 0.15, 0.05, 1.0 ) );
	displayScalarScale.addListener( this, &inkApp::setDisplayScalarScale );
	visualizeParameters.add( velocityFieldScale.set( "velocity scale", 0.1, 0.0, 0.5 ) );
	velocityFieldScale.addListener( this, &inkApp::setVelocityFieldScale );
	visualizeParameters.add( temperatureFieldScale.set( "temperature scale", 0.1, 0.0, 0.5 ) );
	temperatureFieldScale.addListener( this, &inkApp::setTemperatureFieldScale );
	visualizeParameters.add( pressureFieldScale.set( "pressure scale", 0.02, 0.0, 0.5 ) );
	pressureFieldScale.addListener( this, &inkApp::setPressureFieldScale );
	visualizeParameters.add( velocityLineSmooth.set( "line smooth", false ) );
	velocityLineSmooth.addListener( this, &inkApp::setVelocityLineSmooth );

	gui.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	gui.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	gui.add( visualizeParameters );

	gui.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	gui.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	gui.add( velocityDots.parameters );

	// if the settings file is not present the parameters will not be set 
	// during this setup
	if( !ofFile( "settings.xml" ) )
		gui.saveToFile( "settings.xml" );

	gui.loadFromFile( "settings.xml" );

	gui.minimizeAll();
	toggleGuiDraw = false;
}

//-------------------------------------------------------------------------------------------------
void inkApp::update()
{
	deltaTime = ofGetElapsedTimef() - lastTime;
	lastTime = ofGetElapsedTimef();

	switch(gameState)
	{
	case START:
	{

		break;
	}
	case GAME:
	{
		player->update();

		for(int i = 0; i < bullets.size(); ++i)
		{
			bullets[i]->update();
			shared_ptr<inkCharacterController> bulCharCon = bullets[ i ]->get<inkCharacterController>();

			if( bulCharCon->collisionLayer == 0)
			{
				bullets[ i ]->pos.y -= bulCharCon->speed;
			}
			else
			{
				bullets[ i ]->pos.y += bulCharCon->speed;
			}

			ofPoint pos = bullets[ i ]->pos;
			float width = bullets[ i ]->get<inkCharacterController>()->width;
			if(pos.y - width /2 < 0 || pos.y + width /2 > ofGetHeight())
			{
				bullets.erase( bullets.begin() + i );
			}
		}

		for(int i = 0; i < bullets.size(); ++i)
		{
			if(bullets[i]->get<inkCharacterController>()->collisionLayer == 0)
			{
				for(int e = enemies.size()-1; e >= 0 && i < bullets.size(); --e)
				{
					if(ofDist(bullets[i]->pos.x, bullets[i]->pos.y, enemies[e]->pos.x, enemies[e]->pos.y) 
						< (enemies[e]->get<inkCharacterController>()->width + bullets[i]->get<inkCharacterController>()->width)/2)
					{
						enemies.erase( enemies.begin() + e );
						bullets.erase( bullets.begin() + i );
						score += 10;
					}
				}
			}
			else if ( ofDist( bullets[ i ]->pos.x, bullets[ i ]->pos.y, player->pos.x, player->pos.y )
					  < ( player->get<inkCharacterController>()->width + bullets[ i ]->get<inkCharacterController>()->width ) / 2 )
			{
				bullets.erase( bullets.begin() + i );
				lives--;

				if( lives <= 0 )
					gameState = END;
			}
		}

		for (int i = 0; i < enemies.size(); ++i)
		{
			enemies[ i ]->update();
			enemies[ i ]->pos.y += enemies[ i ]->get<inkCharacterController>()->speed;
			enemies[ i ]->pos.x += enemies[ i ]->get<inkOffenseComponent>()->amplitude * sin( ofGetElapsedTimef() );
			if( ofGetElapsedTimef() - enemies[ i ]->get<inkOffenseComponent>()->startShoot > enemies[ i ]->get<inkOffenseComponent>()->shootInterval )
			{
				enemies[ i ]->get<inkOffenseComponent>()->startShoot = ofGetElapsedTimef();
				shared_ptr<inkGameObject> b = gameObjectFactory.create( BULLET );
				b->pos = enemies[ i ]->pos;
				b->get<inkCharacterController>()->collisionLayer = 1;
				b->get<inkCharacterController>()->speed = enemies[ i ]->get<inkCharacterController>()->speed + 3;
				b->get<inkSpriteComponent>()->img = make_shared<ofImage>( enemyBulletImage );
				bullets.push_back( b );
			}
		}

		if(levelController.shouldSpawn())
		{
			shared_ptr<inkGameObject> e = gameObjectFactory.create( ENEMY );
			e->pos.x = ofRandom( ofGetWidth() );
			e->pos.y = 0;
			e->get<inkSpriteComponent>()->img = make_shared<ofImage>(enemyImage);
			e->get<inkCharacterController>()->width = enemyImage.getWidth();
			e->get<inkCharacterController>()->speed = ofRandom( 2, 7 );
			e->get<inkOffenseComponent>()->amplitude = ofRandom( maxEnemyAmplitude );
			e->get<inkOffenseComponent>()->shootInterval = ofRandom( 0.5, maxEnemyAmplitude );
			e->get<inkOffenseComponent>()->startShoot = ofGetElapsedTimef();
			enemies.push_back( e );
		}

		break;
	}
	case END:
	{

		break;
	}
	case FLOW:
	{
		simpleCam.update();

		if( simpleCam.isFrameNew() )
		{
			ofPushStyle();
			ofEnableBlendMode( OF_BLENDMODE_DISABLED );
			cameraFbo.begin();

			if( doFlipCamera )
				simpleCam.draw( cameraFbo.getWidth()
								, 0
								, -cameraFbo.getWidth()
								, cameraFbo.getHeight()
				);  // Flip Horizontal
			else
				simpleCam.draw( 0, 0, cameraFbo.getWidth(), cameraFbo.getHeight() );
			cameraFbo.end();
			ofPopStyle();

			opticalFlow.setSource( cameraFbo.getTexture() );

			// opticalFlow.update(deltaTime);
			// use internal deltatime instead
			opticalFlow.update();

			velocityMask.setDensity( cameraFbo.getTexture() );
			velocityMask.setVelocity( opticalFlow.getOpticalFlow() );
			velocityMask.update();
		}


		fluidSimulation.addVelocity( opticalFlow.getOpticalFlowDecay() );
		fluidSimulation.addDensity( velocityMask.getColorMask() );
		fluidSimulation.addTemperature( velocityMask.getLuminanceMask() );

		inputForces.update( deltaTime );

		for( int i = 0; i < inputForces.getNumForces(); i++ )
		{
			if( inputForces.didChange( i ) )
			{
				switch( inputForces.getType( i ) )
				{
				case FT_DENSITY:
					fluidSimulation.addDensity
					( inputForces.getTextureReference( i )
					  , inputForces.getStrength( i )
					  , false );
					break;
				case FT_VELOCITY:
					fluidSimulation.addVelocity
					( inputForces.getTextureReference( i )
					  , inputForces.getStrength( i )
					  , false );
					particleFlow.addFlowVelocity
					( inputForces.getTextureReference( i )
					  , inputForces.getStrength( i ) );
					break;
				case FT_TEMPERATURE:
					fluidSimulation.addTemperature
					( inputForces.getTextureReference( i )
					  , inputForces.getStrength( i )
					  , false );
					break;
				case FT_PRESSURE:
					fluidSimulation.addPressure
					( inputForces.getTextureReference( i )
					  , inputForces.getStrength( i )
					  , false );
					break;
				case FT_OBSTACLE:
					fluidSimulation.addTempObstacle
					( inputForces.getTextureReference( i ) );
				default:
					break;
				}
			}
		}

		fluidSimulation.update();

		if( particleFlow.isActive() )
		{
			particleFlow.setSpeed( fluidSimulation.getSpeed() );
			particleFlow.setCellSize( fluidSimulation.getCellSize() );
			particleFlow.addFlowVelocity( opticalFlow.getOpticalFlow() );
			particleFlow.addFluidVelocity( fluidSimulation.getVelocity() );
			//		particleFlow.addDensity(fluidSimulation.getDensity());
			particleFlow.setObstacle( fluidSimulation.getObstacle() );
		}
		particleFlow.update();
		break;
	}
	default:
		break;
	}
}

//-------------------------------------------------------------------------------------------------
void inkApp::keyPressed( int key )
{
	switch( gameState )
	{
	case START:
	{
		switch( key )
		{
		case ' ':
		{
			gameState = GAME;
			levelController.setup( ofGetElapsedTimeMillis() );
			break;
		}
		default: break;
		}
		break;
	}
	case GAME:
	{
		switch( key )
		{
		case 'w':
		case 'W':
		case OF_KEY_UP:
		{
			player->get<inkCharacterController>()->isUpPressed = true;
			break;
		}

		case 'a':
		case 'A':
		case OF_KEY_LEFT:
		{
			player->get<inkCharacterController>()->isLeftPressed = true;
			break;
		}

		case 's':
		case 'S':
		case OF_KEY_DOWN:
		{
			player->get<inkCharacterController>()->isDownPressed = true;
			break;
		}

		case 'd':
		case 'D':
		case OF_KEY_RIGHT:
		{
			player->get<inkCharacterController>()->isRightPressed = true;
			break;
		}

		case ' ':
		{
			shared_ptr<inkGameObject> b = gameObjectFactory.create( BULLET );
			b->pos = player->pos;
			b->get<inkCharacterController>()->collisionLayer = 0;
			b->get<inkCharacterController>()->speed = player->get<inkCharacterController>()->speed + 3;
			b->get<inkSpriteComponent>()->img = make_shared<ofImage>(playerBulletImage);
			bullets.push_back( b );
			break;
		}

		default: break;
		}

		break;
	}
	case END:
	{
		break;
	}
	case FLOW:
	{
		switch( key )
		{
		case 'G':
		case 'g': toggleGuiDraw = !toggleGuiDraw; break;
		case 'f':
		case 'F': doFullScreen.set( !doFullScreen.get() ); break;
		case 'c':
		case 'C': doDrawCamBackground.set( !doDrawCamBackground.get() ); break;

		case '1': drawMode.set( DRAW_COMPOSITE ); break;
		case '2': drawMode.set( DRAW_FLUID_FIELDS ); break;
		case '3': drawMode.set( DRAW_FLUID_VELOCITY ); break;
		case '4': drawMode.set( DRAW_FLUID_PRESSURE ); break;
		case '5': drawMode.set( DRAW_FLUID_TEMPERATURE ); break;
		case '6': drawMode.set( DRAW_OPTICAL_FLOW ); break;
		case '7': drawMode.set( DRAW_FLOW_MASK ); break;
		case '8': drawMode.set( DRAW_MOUSE ); break;

		case 'r':
		case 'R':
			fluidSimulation.reset();
			fluidSimulation.addObstacle( flowToolsLogoImage.getTexture() );
			inputForces.reset();
			break;

		case 'i':
		case 'I':
			fluidSimulation.invert();
			particleFlow.invert();
			break;

		default: break;
		}
		break;
	}
	default: break;
	}
	
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawModeSetName( int &_value )
{
	switch( _value )
	{
	case DRAW_COMPOSITE:		drawName.set( "Composite      (1)" ); break;
	case DRAW_PARTICLES:		drawName.set( "Particles      " ); break;
	case DRAW_FLUID_FIELDS:		drawName.set( "Fluid Fields   (2)" ); break;
	case DRAW_FLUID_DENSITY:	drawName.set( "Fluid Density  " ); break;
	case DRAW_FLUID_VELOCITY:	drawName.set( "Fluid Velocity (3)" ); break;
	case DRAW_FLUID_PRESSURE:	drawName.set( "Fluid Pressure (4)" ); break;
	case DRAW_FLUID_TEMPERATURE:drawName.set( "Fld Temperature(5)" ); break;
	case DRAW_FLUID_DIVERGENCE: drawName.set( "Fld Divergence " ); break;
	case DRAW_FLUID_VORTICITY:	drawName.set( "Fluid Vorticity" ); break;
	case DRAW_FLUID_BUOYANCY:	drawName.set( "Fluid Buoyancy " ); break;
	case DRAW_FLUID_OBSTACLE:	drawName.set( "Fluid Obstacle " ); break;
	case DRAW_OPTICAL_FLOW:		drawName.set( "Optical Flow   (6)" ); break;
	case DRAW_FLOW_MASK:		drawName.set( "Flow Mask      (7)" ); break;
	case DRAW_SOURCE:			drawName.set( "Source         " ); break;
	case DRAW_MOUSE:			drawName.set( "Left Mouse     (8)" ); break;
	case DRAW_VELDOTS:			drawName.set( "VelDots        (0)" ); break;
	}
}

//-------------------------------------------------------------------------------------------------
void inkApp::draw()
{
	switch(gameState)
	{
	case START:
	{
		break;
	}
	case GAME:
	{
		ofBackground( 0, 0, 0 );
		player->get<inkSpriteComponent>()->draw();

		for(auto&& b : bullets)
		{
			b->get<inkSpriteComponent>()->draw();
		}

		for(auto&& e : enemies)
		{
			e->get<inkSpriteComponent>()->draw();
		}

		break;
	}
	case END:
	{
		break;
	}
	case FLOW:
	{
		//glClearColor(0.3f, 0.4f, 0.1f, 1.0f);
		//ofColor::white
		//ofClear(ofColor(128,128,128,255));
		if( fluidSimulation.isInverted() )
			ofClear( 255, 255 );
		else
			ofClear( 0, 0 );
		//ofBackground(ofColor::white);
		//ofBackground(ofColor(255, 255, 255, 255));
		if( doDrawCamBackground.get() )
			drawSource();


		if( !toggleGuiDraw )
		{
			//ofHideCursor();
			drawComposite();
		}
		else
		{
			ofShowCursor();
			switch( drawMode.get() )
			{
			case DRAW_COMPOSITE: drawComposite(); break;
			case DRAW_PARTICLES: drawParticles(); break;
			case DRAW_FLUID_FIELDS: drawFluidFields(); break;
			case DRAW_FLUID_DENSITY: drawFluidDensity(); break;
			case DRAW_FLUID_VELOCITY: drawFluidVelocity(); break;
			case DRAW_FLUID_PRESSURE: drawFluidPressure(); break;
			case DRAW_FLUID_TEMPERATURE: drawFluidTemperature(); break;
			case DRAW_FLUID_DIVERGENCE: drawFluidDivergence(); break;
			case DRAW_FLUID_VORTICITY: drawFluidVorticity(); break;
			case DRAW_FLUID_BUOYANCY: drawFluidBuoyance(); break;
			case DRAW_FLUID_OBSTACLE: drawFluidObstacle(); break;
			case DRAW_FLOW_MASK: drawMask(); break;
			case DRAW_OPTICAL_FLOW: drawOpticalFlow(); break;
			case DRAW_SOURCE: drawSource(); break;
			case DRAW_MOUSE: drawMouseForces(); break;
			case DRAW_VELDOTS: drawVelocityDots(); break;
			}
			drawGui();
		}
		break;
	}
	default:
		break;
	}
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawComposite( int _x, int _y, int _width, int _height )
{
	ofPushStyle();

	ofEnableBlendMode( OF_BLENDMODE_ALPHA );
	fluidSimulation.draw( _x, _y, _width, _height );

	ofEnableBlendMode( OF_BLENDMODE_ALPHA );
	if( particleFlow.isActive() )
		particleFlow.draw( _x, _y, _width, _height );

	if( showLogo )
	{
		flowToolsLogoImage.draw( _x, _y, _width, _height );
	}

	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawParticles( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	ofEnableBlendMode( OF_BLENDMODE_ALPHA );
	if( particleFlow.isActive() )
		particleFlow.draw( _x, _y, _width, _height );
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawFluidFields( int _x, int _y, int _width, int _height )
{
	ofPushStyle();

	ofEnableBlendMode( OF_BLENDMODE_ALPHA );
	pressureField.setPressure( fluidSimulation.getPressure() );
	pressureField.draw( _x, _y, _width, _height );
	velocityTemperatureField.setVelocity( fluidSimulation.getVelocity() );
	velocityTemperatureField.setTemperature( fluidSimulation.getTemperature() );
	velocityTemperatureField.draw( _x, _y, _width, _height );
	temperatureField.setTemperature( fluidSimulation.getTemperature() );

	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawFluidDensity( int _x, int _y, int _width, int _height )
{
	ofPushStyle();

	fluidSimulation.draw( _x, _y, _width, _height );

	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawFluidVelocity( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	if( showScalar.get() )
	{
		ofClear( 0, 0 );
		ofEnableBlendMode( OF_BLENDMODE_ALPHA );
		//	ofEnableBlendMode(OF_BLENDMODE_DISABLED); // altenate mode
		displayScalar.setSource( fluidSimulation.getVelocity() );
		displayScalar.draw( _x, _y, _width, _height );
	}
	if( showField.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_ADD );
		velocityField.setVelocity( fluidSimulation.getVelocity() );
		velocityField.draw( _x, _y, _width, _height );
	}
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawFluidPressure( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	ofClear( 128 );
	if( showScalar.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_DISABLED );
		displayScalar.setSource( fluidSimulation.getPressure() );
		displayScalar.draw( _x, _y, _width, _height );
	}
	if( showField.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_ALPHA );
		pressureField.setPressure( fluidSimulation.getPressure() );
		pressureField.draw( _x, _y, _width, _height );
	}
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawFluidTemperature( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	if( showScalar.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_DISABLED );
		displayScalar.setSource( fluidSimulation.getTemperature() );
		displayScalar.draw( _x, _y, _width, _height );
	}
	if( showField.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_ADD );
		temperatureField.setTemperature( fluidSimulation.getTemperature() );
		temperatureField.draw( _x, _y, _width, _height );
	}
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawFluidDivergence( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	if( showScalar.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_DISABLED );
		displayScalar.setSource( fluidSimulation.getDivergence() );
		displayScalar.draw( _x, _y, _width, _height );
	}
	if( showField.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_ADD );
		temperatureField.setTemperature( fluidSimulation.getDivergence() );
		temperatureField.draw( _x, _y, _width, _height );
	}
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawFluidVorticity( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	if( showScalar.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_DISABLED );
		displayScalar.setSource( fluidSimulation.getConfinement() );
		displayScalar.draw( _x, _y, _width, _height );
	}
	if( showField.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_ADD );
		ofSetColor( 255, 255, 255, 255 );
		velocityField.setVelocity( fluidSimulation.getConfinement() );
		velocityField.draw( _x, _y, _width, _height );
	}
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawFluidBuoyance( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	if( showScalar.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_DISABLED );
		displayScalar.setSource( fluidSimulation.getSmokeBuoyancy() );
		displayScalar.draw( _x, _y, _width, _height );
	}
	if( showField.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_ADD );
		velocityField.setVelocity( fluidSimulation.getSmokeBuoyancy() );
		velocityField.draw( _x, _y, _width, _height );
	}
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawFluidObstacle( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	ofEnableBlendMode( OF_BLENDMODE_DISABLED );
	fluidSimulation.getObstacle().draw( _x, _y, _width, _height );
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawMask( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	ofEnableBlendMode( OF_BLENDMODE_DISABLED );
	velocityMask.draw( _x, _y, _width, _height );
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawOpticalFlow( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	if( showScalar.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_ALPHA );
		displayScalar.setSource( opticalFlow.getOpticalFlowDecay() );
		displayScalar.draw( 0, 0, _width, _height );
	}
	if( showField.get() )
	{
		ofEnableBlendMode( OF_BLENDMODE_ADD );
		velocityField.setVelocity( opticalFlow.getOpticalFlowDecay() );
		velocityField.draw( 0, 0, _width, _height );
	}
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawSource( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	ofEnableBlendMode( OF_BLENDMODE_DISABLED );
	cameraFbo.draw( _x, _y, _width, _height );
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawMouseForces( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	ofClear( 0, 0 );

	for( int i = 0; i < inputForces.getNumForces(); i++ )
	{
		ofEnableBlendMode( OF_BLENDMODE_ADD );
		if( inputForces.didChange( i ) )
		{
			ftDrawForceType dfType = inputForces.getType( i );
			if( dfType == FT_DENSITY )
				inputForces.getTextureReference( i )
				.draw( _x, _y, _width, _height );
		}
	}

	for( int i = 0; i < inputForces.getNumForces(); i++ )
	{
		ofEnableBlendMode( OF_BLENDMODE_ALPHA );
		if( inputForces.didChange( i ) )
		{
			switch( inputForces.getType( i ) )
			{
			case FT_VELOCITY:
				velocityField.setVelocity( inputForces.getTextureReference( i ) );
				velocityField.draw( _x, _y, _width, _height );
				break;
			case FT_TEMPERATURE:
				temperatureField.setTemperature( inputForces
												 .getTextureReference( i ) );
				temperatureField.draw( _x, _y, _width, _height );
				break;
			case FT_PRESSURE:
				pressureField.setPressure( inputForces.getTextureReference( i ) );
				pressureField.draw( _x, _y, _width, _height );
				break;
			default:
				break;
			}
		}
	}

	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawVelocityDots( int _x, int _y, int _width, int _height )
{
	ofPushStyle();
	ofEnableBlendMode( OF_BLENDMODE_ADD );
	velocityDots.setVelocity( fluidSimulation.getVelocity() );
	velocityDots.draw( _x, _y, _width, _height );
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::drawGui()
{
	guiFPS = (int)( ofGetFrameRate() + 0.5 );

	// calculate minimum fps
	deltaTimeDeque.push_back( deltaTime );

	while( deltaTimeDeque.size() > guiFPS.get() )
		deltaTimeDeque.pop_front();

	float longestTime = 0;
	for( int i = 0; i < deltaTimeDeque.size(); i++ )
	{
		if( deltaTimeDeque[ i ] > longestTime )
			longestTime = deltaTimeDeque[ i ];
	}

	guiMinFPS.set( 1.0 / longestTime );


	ofPushStyle();
	ofEnableBlendMode( OF_BLENDMODE_ALPHA );
	gui.draw();

	// HACK TO COMPENSATE FOR DISSAPEARING MOUSE
	ofEnableBlendMode( OF_BLENDMODE_SUBTRACT );
	ofDrawCircle( ofGetMouseX(), ofGetMouseY(), ofGetWindowWidth() / 300.0 );
	ofEnableBlendMode( OF_BLENDMODE_ADD );
	ofDrawCircle( ofGetMouseX(), ofGetMouseY(), ofGetWindowWidth() / 600.0 );
	ofPopStyle();
}

//-------------------------------------------------------------------------------------------------
void inkApp::keyReleased( int key )
{
	switch( gameState )
	{
	case START:
	{
		break;
	}
	case GAME:
	{
		switch( key )
		{
		case 'w':
		case 'W':
		case OF_KEY_UP:
		{
			player->get<inkCharacterController>()->isUpPressed = false;
			break;
		}

		case 'a':
		case 'A':
		case OF_KEY_LEFT:
		{
			player->get<inkCharacterController>()->isLeftPressed = false;
			break;
		}

		case 's':
		case 'S':
		case OF_KEY_DOWN:
		{
			player->get<inkCharacterController>()->isDownPressed = false;
			break;
		}

		case 'd':
		case 'D':
		case OF_KEY_RIGHT:
		{
			player->get<inkCharacterController>()->isRightPressed = false;
			break;
		}

		default: break;
		}

		break;
	}
	case END:
	{
		break;
	}
	case FLOW:
	{
		break;
	}
	default: break;
	}
}

//-------------------------------------------------------------------------------------------------
void inkApp::mouseMoved( int x, int y )
{

}

//-------------------------------------------------------------------------------------------------
void inkApp::mouseDragged( int x, int y, int button )
{

}

//-------------------------------------------------------------------------------------------------
void inkApp::mousePressed( int x, int y, int button )
{

}

//-------------------------------------------------------------------------------------------------
void inkApp::mouseReleased( int x, int y, int button )
{

}

//-------------------------------------------------------------------------------------------------
void inkApp::mouseEntered( int x, int y )
{

}

//-------------------------------------------------------------------------------------------------
void inkApp::mouseExited( int x, int y )
{

}

//-------------------------------------------------------------------------------------------------
void inkApp::windowResized( int w, int h )
{

}

//-------------------------------------------------------------------------------------------------
void inkApp::gotMessage( ofMessage msg )
{

}

//-------------------------------------------------------------------------------------------------
void inkApp::dragEvent( ofDragInfo dragInfo )
{

}
