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
#include <sstream>

using namespace ink;
using namespace flowTools;

//InkwellColor inkApp::inkColor;

//-------------------------------------------------------------------------------------------------
void inkApp::setup()
{
#ifdef DEBUG_GL_ERRORS
	std::stringstream ss;
	ss << "GL Error 1 = " << glGetError() << std::endl;
    GLint result;
	ss << "GL Error 1a = " << glGetError() << std::endl;
    ss << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &result);
    ss << result << std::endl;
	ofLogNotice( ss.str() );
#endif // DEBUG_GL_ERRORS


	ofSetVerticalSync(false);
	//ofSetFrameRate(60);
	ofSetLogLevel(OF_LOG_NOTICE);
	//ofSetFullscreen(true);
	//ofSetBackgroundAuto(true);
	//ofSetBackgroundColor(ofColor(255,255,255,127));
    
	player = gameObjectFactory.create( PLAYER );

	gameState = GAME;
	//score = 0;
	//lives = 3;
    ignoreDoubleTouch = false;

	//playerImage.load( "player.png" );
	//enemyImage.load( "enemy0.png" );
	//playerBulletImage.load( "player_bullet.png" );
	//enemyBulletImage.load( "enemy_bullet.png" );
	//lifeImage.load( "life_image.png" );

	butterflyImage.load( "butterfly.png" );
	butterflyLineImage.load( "butterfly_line.png" );
	splashHDImage.load( "splash_fhd.png" );
	splashiPadImage.load( "splash_ipad.png" );
	//redButtonImage.load( "redButton.png" );
	//greenButtonImage.load( "greenButton.png" );
	//blueButtonImage.load( "blueButton.png" );

	startScreen.load( "start_screen.png" );
	//endScreen.load( "end_screen.png" );
	//scoreFont.load( "Gota_Light.otf", 48 );

	butterflyImage.resize( 541.f / 10.f, 348.f / 10.f );
	butterflyLineImage.resize( 541.f / 10.f, 348.f / 10.f );
	splashHDImage.resize( ofGetWidth(), ofGetHeight() );
	splashiPadImage.resize( ofGetWidth(), ofGetHeight() );

	//player->get<inkSpriteComponent>()->img = make_shared<ofImage>( butterflyImage );
	//player->get<inkCharacterController>()->width = butterflyImage.getWidth();
	//player->get<inkCharacterController>()->height = butterflyImage.getHeight();
	//player->pos.x = ofGetWidth() / 2;
	//player->pos.y = ofGetHeight() / 2;
	//player->get<inkFlowComponent>()->setForce( ofFloatColor( 0, 1, 0, 1 ) );
	//player->get<inkFlowComponent>()->setInitiatlPos( player->pos );

	redInkwell		= gameObjectFactory.create( INKWELL );
	greenInkwell	= gameObjectFactory.create( INKWELL );
	blueInkwell		= gameObjectFactory.create( INKWELL );

	redInkwell->pos.x = ofGetWidth() / 3;
	redInkwell->pos.y = ofGetHeight() / 3;
	redInkwell->get<inkSpriteComponent>()->img = make_shared<ofImage>( butterflyLineImage );
	redInkwell->get<inkCharacterController>()->width = butterflyLineImage.getWidth();
	redInkwell->get<inkCharacterController>()->height = butterflyLineImage.getHeight();
	redInkwell->get<inkFlowComponent>()->setForce( ofFloatColor( 1, 0, 0, 1 ) );
	redInkwell->get<inkFlowComponent>()->setInitiatlPos( redInkwell->pos );
	//redInkwell->get<inkFlowComponent>()->setRadius( 10.f );

	greenInkwell->pos.x = 2 * ofGetWidth() / 3;
	greenInkwell->pos.y = ofGetHeight() / 3;
	greenInkwell->get<inkSpriteComponent>()->img = make_shared<ofImage>( butterflyLineImage );
	greenInkwell->get<inkCharacterController>()->width = butterflyLineImage.getWidth();
	greenInkwell->get<inkCharacterController>()->height = butterflyLineImage.getHeight();
	greenInkwell->get<inkFlowComponent>()->setForce( ofFloatColor( 0, 1, 0, 1 ) );
	greenInkwell->get<inkFlowComponent>()->setInitiatlPos( greenInkwell->pos );
	//greenInkwell->get<inkFlowComponent>()->setRadius( 10.f );

	blueInkwell->pos.x = ofGetWidth() / 2;
	blueInkwell->pos.y = 2 * ofGetHeight() / 3;
	blueInkwell->get<inkSpriteComponent>()->img = make_shared<ofImage>( butterflyLineImage );
	blueInkwell->get<inkCharacterController>()->width = butterflyLineImage.getWidth();
	blueInkwell->get<inkCharacterController>()->height = butterflyLineImage.getHeight();
	blueInkwell->get<inkFlowComponent>()->setForce( ofFloatColor( 0, 0, 1, 1 ) );
	blueInkwell->get<inkFlowComponent>()->setInitiatlPos( blueInkwell->pos );
	//blueInkwell->get<inkFlowComponent>()->setRadius( 10.f );


	//maxEnemyAmplitude = 3.0;
	//maxEnemyShootInterval = 1.5;

	//liveTester.setup();

	//liveTester.enemyIntervalTime = 2500;
	//liveTester.maxEnemyAmplitude = 3.0;
	//liveTester.maxEnemyShootInterval = 1.5;
	//liveTester.triggerBonus = false;


	drawWidth = ofGetWidth() / 8;
	drawHeight = ofGetHeight() / 8;
	// process all but the density on 16th resolution
	flowWidth = drawWidth / 4;
	flowHeight = drawHeight / 4;
    
    ofLogNotice(string("GLSL Version = ") + string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION)) + string("\n"));

	// FLOW & MASK
	//opticalFlow.setup( flowWidth, flowHeight );
	//velocityMask.setup( drawWidth, drawHeight );
    
#ifdef DEBUG_GL_ERRORS
	ss.clear();
    ss << "GL Error 1b = " << glGetError() << std::endl;
    ss << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &result);
    ss << result << std::endl;
    ofLogNotice( ss.str() );
#endif // DEBUG_GL_ERRORS

	// FLUID & PARTICLES
	fluidSimulation.setup( flowWidth, flowHeight, drawWidth, drawHeight );
	//particleFlow.setup( flowWidth, flowHeight, drawWidth, drawHeight );
    
#ifdef DEBUG_GL_ERRORS
	ss.clear();
    ss << "GL Error 1c = " << glGetError() << std::endl;
    ss << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
    ofLogNotice( ss.str() );
#endif // DEBUG_GL_ERRORS

	//flowToolsLogoImage.load( "inkling.png" );
	//fluidSimulation.addObstacle( flowToolsLogoImage.getTexture() );
	//showLogo = false;

	//velocityDots.setup( flowWidth / 4, flowHeight / 4 );
    
#ifdef DEBUG_GL_ERRORS
    ss.clear();
    ss << "GL Error 1d = " << glGetError() << std::endl;
    ss << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
    ofLogNotice( ss.str() );
#endif // DEBUG_GL_ERRORS

	// VISUALIZATION
	//displayScalar.setup( flowWidth, flowHeight );
	//velocityField.setup( flowWidth / 4, flowHeight / 4 );
	//temperatureField.setup( flowWidth / 4, flowHeight / 4 );
	//pressureField.setup( flowWidth / 4, flowHeight / 4 );
	//velocityTemperatureField.setup( flowWidth / 4, flowHeight / 4 );
    
#ifdef DEBUG_GL_ERRORS
    ss.clear();
    ss << "GL Error 1e = " << glGetError() << std::endl;
    ss << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
    ofLogNotice( ss.str() );
#endif // DEBUG_GL_ERRORS

	// MOUSE & TOUCH DRAW
	//inputForces.setup( flowWidth, flowHeight, drawWidth, drawHeight );

	// CAMERA
//	simpleCam.setup(640, 480, true);
//	didCamUpdate = true;
//	cameraFbo.allocate(640, 480);
//	cameraFbo.black();
    
#ifdef DEBUG_GL_ERRORS
    ss.clear();
    ss << "GL Error 1f = " << glGetError() << std::endl;
    ofLogNotice( ss.str() );
#endif // DEBUG_GL_ERRORS

	ofAddListener( ofEvents().touchDoubleTap, this, &inkApp::touchDoubleTap );

	// GUI
	//setupGui();

	//mouseForces.invertForce(0);
	//mouseForces.invertForce(3);

	lastTime = ofGetElapsedTimef();
    
#ifdef DEBUG_GL_ERRORS
	ss.clear();
    ss << "GL Error 2 = " << glGetError() << std::endl;
    ofLogNotice(ss.str());
#endif // DEBUG_GL_ERRORS

    //toggleGuiDraw = false;
    
    drawMode.set(DRAW_COMPOSITE);
    
}

void inkApp::touchDoubleTap( ofTouchEventArgs & touch )
{
    if(ignoreDoubleTouch)
    {
        //toggleGuiDraw = !toggleGuiDraw;
        //
        //drawMode.set((drawMode.get() + 1) % drawMode.getMax());
        //
        //gameState = (GameState)((gameState+1)%(NO_GAME_STATE+1));
        //levelController.setup( ofGetElapsedTimeMillis() );
        
        ignoreDoubleTouch = false;
    }
    else
    {

		gameState = GAME;

        ignoreDoubleTouch = true;
    }
    
}

//void inkApp::redButtonPressed()
//{
//	for( int i = 0; i < inputForces.getNumForces(); ++i )
//	{
//		inputForces.setColor( i, ofColor::red );
//	}
//}
//
//void inkApp::greenButtonPressed()
//{
//	for( int i = 0; i < inputForces.getNumForces(); ++i )
//	{
//		inputForces.setColor( i, ofColor::green );
//	}
//}
//
//void inkApp::blueButtonPressed()
//{
//	for( int i = 0; i < inputForces.getNumForces(); ++i )
//	{
//		inputForces.setColor( i, ofColor::blue );
//	}
//}

//-------------------------------------------------------------------------------------------------
void inkApp::setupGui()
{
	settingsPanel.setup( "settings" );
	settingsPanel.setDefaultBackgroundColor( ofColor( 0, 0, 0, 127 ) );
	settingsPanel.setDefaultFillColor( ofColor( 160, 160, 160, 160 ) );
	settingsPanel.add( guiFPS.set( "average FPS", 0, 0, 60 ) );
	settingsPanel.add( guiMinFPS.set( "minimum FPS", 0, 0, 60 ) );
	settingsPanel.add( doFullScreen.set( "fullscreen (F)", false ) );
	doFullScreen.addListener( this, &inkApp::setFullScreen );
	settingsPanel.add( toggleGuiDraw.set( "show gui (G)", false ) );
	settingsPanel.add( doFlipCamera.set( "flip camera", true ) );
	settingsPanel.add( doDrawCamBackground.set( "draw camera (C)", false ) );

	settingsPanel.add( drawMode.set( "draw mode"
						   , DRAW_FLUID_DENSITY
						   , DRAW_FLUID_DENSITY
						   , DRAW_MOUSE
	)
	);

	drawMode.addListener( this, &inkApp::drawModeSetName );
	settingsPanel.add( drawName.set( "MODE", "draw name" ) );

	int guiColorSwitch = 0;
	ofColor guiHeaderColor[ 2 ];
	guiHeaderColor[ 0 ].set( 160, 160, 80, 200 );
	guiHeaderColor[ 1 ].set( 80, 160, 160, 200 );
	ofColor guiFillColor[ 2 ];
	guiFillColor[ 0 ].set( 160, 160, 80, 200 );
	guiFillColor[ 1 ].set( 80, 160, 160, 200 );

	settingsPanel.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	settingsPanel.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	settingsPanel.add( opticalFlow.parameters );

	settingsPanel.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	settingsPanel.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	settingsPanel.add( velocityMask.parameters );

	settingsPanel.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	settingsPanel.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	settingsPanel.add( fluidSimulation.parameters );

	settingsPanel.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	settingsPanel.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	settingsPanel.add( particleFlow.parameters );

	//settingsPanel.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	//settingsPanel.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	//guiColorSwitch = 1 - guiColorSwitch;
	//settingsPanel.add( inputForces.leftButtonParameters );

	//settingsPanel.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	//settingsPanel.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	//guiColorSwitch = 1 - guiColorSwitch;
	//settingsPanel.add( inputForces.rightButtonParameters );

	//settingsPanel.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	//settingsPanel.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	//guiColorSwitch = 1 - guiColorSwitch;
	//settingsPanel.add( inputForces.middleButtonParameters );

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

	settingsPanel.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	settingsPanel.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	settingsPanel.add( visualizeParameters );

	settingsPanel.setDefaultHeaderBackgroundColor( guiHeaderColor[ guiColorSwitch ] );
	settingsPanel.setDefaultFillColor( guiFillColor[ guiColorSwitch ] );
	guiColorSwitch = 1 - guiColorSwitch;
	settingsPanel.add( velocityDots.parameters );

	// if the settings file is not present the parameters will not be set 
	// during this setup
	if( !ofFile( "settings.xml" ) )
		settingsPanel.saveToFile( "settings.xml" );

	settingsPanel.loadFromFile( "settings.xml" );

	settingsPanel.minimizeAll();
	toggleGuiDraw = false;

	////buttonsPanel.setup( "buttons" );
	////buttonsPanel.setPosition( 200, ofGetHeight() - 200 );
	////buttonsPanel.setShape( 200, ofGetHeight() - 200, ofGetWidth() - 400, 150 );

	//redButton.setup( "redButton", 200, 200 );
	//redButton.setBackgroundColor( ofColor::red );
	//redButton.setFillColor( ofColor::red );
	//redButton.setBorderColor( ofColor::red );
	//redButton.addListener( this, &inkApp::redButtonPressed );
	//redButton.setShape( 200, ofGetHeight() - 200, 200, 100 );
	//redButton.setTextColor( ofColor( 0, 0 ) );
	////redButton.setSize( 200, 200 );
	////buttonsPanel.add( &redButton );

	//greenButton.setup( "greenButton", 200, 200 );
	//greenButton.setBackgroundColor( ofColor::green );
	//greenButton.setFillColor( ofColor::green );
	//greenButton.setBorderColor( ofColor::green );
	//greenButton.addListener( this, &inkApp::greenButtonPressed );
	//greenButton.setShape( 450, ofGetHeight() - 200, 200, 100 );
	//greenButton.setTextColor( ofColor( 0, 0 ) );
	////greenButton.setSize( 200, 200 );
	////buttonsPanel.add( &greenButton );

	//blueButton.setup( "blueButton", 200, 200 );
	//blueButton.setBackgroundColor( ofColor::blue );
	//blueButton.setFillColor( ofColor::blue );
	//blueButton.setBorderColor( ofColor::blue );
	//blueButton.addListener( this, &inkApp::blueButtonPressed );
	//blueButton.setShape( 700, ofGetHeight() - 200, 200, 100 );
	//blueButton.setTextColor( ofColor( 0, 0 ) );
	////blueButton.setSize( 200, 200 );
	////buttonsPanel.add( &blueButton );

	////buttonsPanel.registerMouseEvents();
}

//-------------------------------------------------------------------------------------------------
void inkApp::update()
{
	deltaTime = ofGetElapsedTimef() - lastTime;
	lastTime = ofGetElapsedTimef();
    
#ifdef DEBUG_GL_ERRORS
	std::stringstream ss;
    ss << "GL Error 3 = " << glGetError() << std::endl;
    ofLogNotice(ss.str());
#endif // DEBUG_GL_ERRORS
    

	switch(gameState)
	{
	case START:
	{

		break;
	}
	case GAME:
	{
		//player->update();
		//liveTester.update();

		redInkwell->update();
		greenInkwell->update();
		blueInkwell->update();

		//levelController.enemyIntervalTime = liveTester.enemyIntervalTime;
		//maxEnemyAmplitude = liveTester.maxEnemyAmplitude;
		//maxEnemyShootInterval = liveTester.maxEnemyShootInterval;
		//levelController.triggerBonus = liveTester.triggerBonus;

		//for(int i = 0; i < bullets.size(); ++i)
		//{
		//	bullets[i]->update();
		//	shared_ptr<inkCharacterController> bulCharCon = bullets[ i ]->get<inkCharacterController>();

		//	if( bulCharCon->collisionLayer == 0)
		//	{
		//		bullets[ i ]->pos.y -= bulCharCon->speed;
		//	}
		//	else
		//	{
		//		bullets[ i ]->pos.y += bulCharCon->speed;
		//	}

		//	ofPoint pos = bullets[ i ]->pos;
		//	float width = bullets[ i ]->get<inkCharacterController>()->width;
		//	if(pos.y - width /2 < 0 || pos.y + width /2 > ofGetHeight())
		//	{
		//		bullets.erase( bullets.begin() + i );
		//	}
		//}

		/*for(int i = 0; i < bullets.size(); ++i)
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
		}*/

		/*for( int i = 0; i < bonuses.size(); ++i )
		{
			bonuses[ i ]->update();
			bonuses[ i ]->pos.y += bonuses[ i ]->get<inkCharacterController>()->speed;

			if( ofDist( player->pos.x, player->pos.y, bonuses[ i ]->pos.x, bonuses[ i ]->pos.y ) < ( player->get<inkCharacterController>()->width + bonuses[ i ]->get<inkCharacterController>()->width / 2 ) )
			{
				lives++;
				bonuses.erase( bonuses.begin() + i );
			}
			else if( bonuses[ i ]->pos.y + bonuses[ i ]->get<inkCharacterController>()->height / 2 > ofGetHeight() )
			{
				bonuses.erase( bonuses.begin() + i );
			}
		}*/



		//for (int i = 0; i < enemies.size(); ++i)
		//{
		//	enemies[ i ]->update();
		//	enemies[ i ]->pos.y += enemies[ i ]->get<inkCharacterController>()->speed;
		//	enemies[ i ]->pos.x += enemies[ i ]->get<inkOffenseComponent>()->amplitude * sin( ofGetElapsedTimef() );
		//	/*if( ofGetElapsedTimef() - enemies[ i ]->get<inkOffenseComponent>()->startShoot > enemies[ i ]->get<inkOffenseComponent>()->shootInterval )
		//	{
		//		enemies[ i ]->get<inkOffenseComponent>()->startShoot = ofGetElapsedTimef();
		//		shared_ptr<inkGameObject> b = gameObjectFactory.create( BULLET );
		//		
		//		b->get<inkCharacterController>()->collisionLayer = 1;
		//		b->get<inkCharacterController>()->width = enemyBulletImage.getWidth();
		//		b->get<inkCharacterController>()->height = enemyBulletImage.getHeight();
		//		b->get<inkCharacterController>()->speed = enemies[ i ]->get<inkCharacterController>()->speed + 3;
		//		b->get<inkSpriteComponent>()->img = make_shared<ofImage>( enemyBulletImage );
		//		b->pos.x = enemies[ i ]->pos.x + enemyImage.getWidth() / 2.f - enemyBulletImage.getWidth() / 2.f;
		//		b->pos.y = enemies[ i ]->pos.y + enemyImage.getHeight() / 2.f - enemyBulletImage.getHeight() / 2.f;
		//		bullets.push_back( b );
		//	}*/

		//	if( enemies[ i ]->pos.y + enemies[ i ]->get<inkCharacterController>()->height / 2 > ofGetHeight() )
		//	{
		//		enemies.erase( enemies.begin() + i );
		//	}
		//}

		//if(levelController.shouldSpawnEnemy())
		//{
		//	shared_ptr<inkGameObject> e = gameObjectFactory.create( ENEMY );
		//	e->pos.x = ofRandom( ofGetWidth() );
		//	e->pos.y = 0;
		//	e->get<inkSpriteComponent>()->img = make_shared<ofImage>(butterflyLineImage);
		//	e->get<inkCharacterController>()->width = butterflyLineImage.getWidth();
		//	e->get<inkCharacterController>()->height = butterflyLineImage.getHeight();
		//	e->get<inkCharacterController>()->speed = ofRandom( 2, 7 );
		//	e->get<inkOffenseComponent>()->amplitude = ofRandom( maxEnemyAmplitude );
		//	e->get<inkOffenseComponent>()->shootInterval = ofRandom( 0.5, maxEnemyAmplitude );
		//	e->get<inkOffenseComponent>()->startShoot = ofGetElapsedTimef();
		//	e->get<inkFlowComponent>()->setForce( ofFloatColor( 1.f, 0.f, 0.f, 1.f ) );
		//	enemies.push_back( e );
		//}

		/*if( levelController.shouldSpawnBonus() )
		{
			std::shared_ptr<inkGameObject> b = gameObjectFactory.create( BONUS );
			b->get<inkSpriteComponent>()->img = make_shared<ofImage>( lifeImage );
			b->get<inkCharacterController>()->width = lifeImage.getWidth();
			b->get<inkCharacterController>()->height = lifeImage.getHeight();
			b->get<inkCharacterController>()->speed = 1;
			b->pos.x = ofRandom( ofGetWidth() );
			b->pos.y = -lifeImage.getHeight() / 2;
			bonuses.push_back( b );
		}*/

		//fluidSimulation.addVelocity( opticalFlow.getOpticalFlowDecay() );
		//fluidSimulation.addDensity( velocityMask.getColorMask() );
		//fluidSimulation.addTemperature( velocityMask.getLuminanceMask() );

		//inputForces.update( deltaTime );

		//for( int i = 0; i < inputForces.getNumForces(); i++ )
		//{
		//	if( inputForces.didChange( i ) )
		//	{
		//		switch( inputForces.getType( i ) )
		//		{
		//		case FT_DENSITY:
		//			fluidSimulation.addDensity
		//			( inputForces.getTextureReference( i )
		//			  , inputForces.getStrength( i )
		//			  , false );
		//			break;
		//		case FT_VELOCITY:
		//			fluidSimulation.addVelocity
		//			( inputForces.getTextureReference( i )
		//			  , inputForces.getStrength( i )
		//			  , false );
		//			particleFlow.addFlowVelocity
		//			( inputForces.getTextureReference( i )
		//			  , inputForces.getStrength( i ) );
		//			break;
		//		case FT_TEMPERATURE:
		//			fluidSimulation.addTemperature
		//			( inputForces.getTextureReference( i )
		//			  , inputForces.getStrength( i )
		//			  , false );
		//			break;
		//		case FT_PRESSURE:
		//			fluidSimulation.addPressure
		//			( inputForces.getTextureReference( i )
		//			  , inputForces.getStrength( i )
		//			  , false );
		//			break;
		//		case FT_OBSTACLE:
		//			fluidSimulation.addTempObstacle
		//			( inputForces.getTextureReference( i ) );
		//		default:
		//			break;
		//		}
		//	}
		//}


		//shared_ptr<inkFlowComponent> f = player->get<inkFlowComponent>();
		//fluidSimulation.addDensity( f->getDensityTexture(), f->getStrength() );
		//fluidSimulation.addVelocity( f->getVelocityTexture(), 1.f );
		//particleFlow.addFlowVelocity( f->getVelocityTexture(), 1.f );
		//fluidSimulation.addTemperature( f->getTemperatureTexture(), 1.f );

		shared_ptr<inkFlowComponent> r = redInkwell->get<inkFlowComponent>();
		fluidSimulation.addDensity( r->getDensityTexture(), r->getStrength() );
		fluidSimulation.addVelocity( r->getVelocityTexture(), 1.f );
		//particleFlow.addFlowVelocity( r->getVelocityTexture(), 1.f );
		fluidSimulation.addTemperature( r->getTemperatureTexture(), 1.f );

		shared_ptr<inkFlowComponent> g = greenInkwell->get<inkFlowComponent>();
		fluidSimulation.addDensity( g->getDensityTexture(), g->getStrength() );
		fluidSimulation.addVelocity( g->getVelocityTexture(), 1.f );
		//particleFlow.addFlowVelocity( g->getVelocityTexture(), 1.f );
		fluidSimulation.addTemperature( g->getTemperatureTexture(), 1.f );

		shared_ptr<inkFlowComponent> b = blueInkwell->get<inkFlowComponent>();
		fluidSimulation.addDensity( b->getDensityTexture(), b->getStrength() );
		fluidSimulation.addVelocity( b->getVelocityTexture(), 1.f );
		//particleFlow.addFlowVelocity( b->getVelocityTexture(), 1.f );
		fluidSimulation.addTemperature( b->getTemperatureTexture(), 1.f );
		

		inkFlowComponent::reset();

		fluidSimulation.update();

		//if( particleFlow.isActive() )
		//{
		//	particleFlow.setSpeed( fluidSimulation.getSpeed() );
		//	particleFlow.setCellSize( fluidSimulation.getCellSize() );
		//	particleFlow.addFlowVelocity( opticalFlow.getOpticalFlow() );
		//	particleFlow.addFluidVelocity( fluidSimulation.getVelocity() );
		//	//		particleFlow.addDensity(fluidSimulation.getDensity());
		//	particleFlow.setObstacle( fluidSimulation.getObstacle() );
		//}
		//particleFlow.update();

		break;
	}
//	case END:
//	{
//
//		break;
//	}
//	case FLOW:
//	{
//		simpleCam.update();
//
//		if( simpleCam.isFrameNew() )
//		{
//			ofPushStyle();
//			ofEnableBlendMode( OF_BLENDMODE_DISABLED );
//			cameraFbo.begin();
//
//			if( doFlipCamera )
//				simpleCam.draw( cameraFbo.getWidth()
//								, 0
//								, -cameraFbo.getWidth()
//								, cameraFbo.getHeight()
//				);  // Flip Horizontal
//			else
//				simpleCam.draw( 0, 0, cameraFbo.getWidth(), cameraFbo.getHeight() );
//			cameraFbo.end();
//			ofPopStyle();
//
//			opticalFlow.setSource( cameraFbo.getTexture() );
//
//			// opticalFlow.update(deltaTime);
//			// use internal deltatime instead
//			opticalFlow.update();
//
//			velocityMask.setDensity( cameraFbo.getTexture() );
//			velocityMask.setVelocity( opticalFlow.getOpticalFlow() );
//			velocityMask.update();
//		}
//        
//#ifdef DEBUG_GL_ERRORS
//        std::stringstream ss;
//        ss << "GL Error 4 = " << glGetError() << std::endl;
//        ofLogNotice(ss.str());
//#endif // DEBUG_GL_ERRORS
//
//
//
//		fluidSimulation.addVelocity( opticalFlow.getOpticalFlowDecay() );
//		fluidSimulation.addDensity( velocityMask.getColorMask() );
//		fluidSimulation.addTemperature( velocityMask.getLuminanceMask() );
//
//		inputForces.update( deltaTime );
//
//#ifdef DEBUG_GL_ERRORS
//        ss.clear();
//        ss << "GL Error 5 = " << glGetError() << std::endl;
//        ofLogNotice(ss.str());
//#endif // DEBUG_GL_ERRORS
//
//
//		for( int i = 0; i < inputForces.getNumForces(); i++ )
//		{
//			if( inputForces.didChange( i ) )
//			{
//				switch( inputForces.getType( i ) )
//				{
//				case FT_DENSITY:
//					fluidSimulation.addDensity
//					( inputForces.getTextureReference( i )
//					  , inputForces.getStrength( i )
//					  , false );
//					break;
//				case FT_VELOCITY:
//					fluidSimulation.addVelocity
//					( inputForces.getTextureReference( i )
//					  , inputForces.getStrength( i )
//					  , false );
//					particleFlow.addFlowVelocity
//					( inputForces.getTextureReference( i )
//					  , inputForces.getStrength( i ) );
//					break;
//				case FT_TEMPERATURE:
//					fluidSimulation.addTemperature
//					( inputForces.getTextureReference( i )
//					  , inputForces.getStrength( i )
//					  , false );
//					break;
//				case FT_PRESSURE:
//					fluidSimulation.addPressure
//					( inputForces.getTextureReference( i )
//					  , inputForces.getStrength( i )
//					  , false );
//					break;
//				case FT_OBSTACLE:
//					fluidSimulation.addTempObstacle
//					( inputForces.getTextureReference( i ) );
//				default:
//					break;
//				}
//			}
//		}
//
//		fluidSimulation.update();
//        
//#ifdef DEBUG_GL_ERRORS
//        ss.clear();
//        ss << "GL Error 6 = " << glGetError() << std::endl;
//        ofLogNotice(ss.str());
//#endif // DEBUG_GL_ERRORS
//
//
//		if( particleFlow.isActive() )
//		{
//			particleFlow.setSpeed( fluidSimulation.getSpeed() );
//			particleFlow.setCellSize( fluidSimulation.getCellSize() );
//			particleFlow.addFlowVelocity( opticalFlow.getOpticalFlow() );
//			particleFlow.addFluidVelocity( fluidSimulation.getVelocity() );
//			//		particleFlow.addDensity(fluidSimulation.getDensity());
//			particleFlow.setObstacle( fluidSimulation.getObstacle() );
//		}
//		particleFlow.update();
//		break;
//	}
	default:
		break;
	}
    
#ifdef DEBUG_GL_ERRORS
    ss.clear();
    ss << "GL Error 7 = " << glGetError() << std::endl;
    ofLogNotice(ss.str());
#endif // DEBUG_GL_ERRORS

}

//-------------------------------------------------------------------------------------------------
void inkApp::keyPressed( int key )
{
	//switch( gameState )
	//{
	//case START:
	//{
	//	switch( key )
	//	{
	//	case ' ':
	//	{
	//		gameState = GAME;
	//		levelController.setup( ofGetElapsedTimeMillis() );
	//		break;
	//	}
	//	default: break;
	//	}
	//	break;
	//}
	//case GAME:
	//{
	//	switch( key )
	//	{
	//	case 'w':
	//	case 'W':
	//	case OF_KEY_UP:
	//	{
	//		player->get<inkCharacterController>()->isUpPressed = true;
	//		break;
	//	}

	//	case 'a':
	//	case 'A':
	//	case OF_KEY_LEFT:
	//	{
	//		player->get<inkCharacterController>()->isLeftPressed = true;
	//		break;
	//	}

	//	case 's':
	//	case 'S':
	//	case OF_KEY_DOWN:
	//	{
	//		player->get<inkCharacterController>()->isDownPressed = true;
	//		break;
	//	}

	//	case 'd':
	//	case 'D':
	//	case OF_KEY_RIGHT:
	//	{
	//		player->get<inkCharacterController>()->isRightPressed = true;
	//		break;
	//	}

	//	case ' ':
	//	{
	//		//shared_ptr<inkGameObject> b = gameObjectFactory.create( BULLET );

	//		//b->get<inkCharacterController>()->collisionLayer = 0;
	//		//b->get<inkCharacterController>()->width = playerBulletImage.getWidth();
	//		//b->get<inkCharacterController>()->height = playerBulletImage.getHeight();
	//		//b->get<inkCharacterController>()->speed = player->get<inkCharacterController>()->speed + 3;
	//		//b->get<inkSpriteComponent>()->img = make_shared<ofImage>(playerBulletImage);
	//		//b->pos.x = player->pos.x + playerImage.getWidth() / 2.f - playerBulletImage.getWidth() / 2.f;
	//		//b->pos.y = player->pos.y + playerImage.getHeight() / 2.f - playerBulletImage.getHeight() / 2.f;
	//		//bullets.push_back( b );
	//		break;
	//	}

	//	case 'G':
	//	case 'g': toggleGuiDraw = !toggleGuiDraw; break;
	//	case 'f':
	//	case 'F': doFullScreen.set( !doFullScreen.get() ); break;
	//	case 'c':
	//	case 'C': doDrawCamBackground.set( !doDrawCamBackground.get() ); break;
	//	case 'e':
	//	case 'E': levelController.spawnEnemy = !levelController.spawnEnemy; break;

	//	case '1': drawMode.set( DRAW_COMPOSITE ); break;
	//	case '2': drawMode.set( DRAW_FLUID_FIELDS ); break;
	//	case '3': drawMode.set( DRAW_FLUID_VELOCITY ); break;
	//	case '4': drawMode.set( DRAW_FLUID_PRESSURE ); break;
	//	case '5': drawMode.set( DRAW_FLUID_TEMPERATURE ); break;
	//	case '6': drawMode.set( DRAW_OPTICAL_FLOW ); break;
	//	case '7': drawMode.set( DRAW_FLOW_MASK ); break;
	//	case '8': drawMode.set( DRAW_MOUSE ); break;

	//	case 'r':
	//	case 'R':
	//		fluidSimulation.reset();
	//		fluidSimulation.addObstacle( flowToolsLogoImage.getTexture() );
	//		inputForces.reset();
	//		for( int i = 0; i < enemies.size(); ++i )
	//			enemies[ i ]->get<inkFlowComponent>()->reset();
	//		break;

	//	case 'i':
	//	case 'I':
	//		fluidSimulation.invert();
	//		particleFlow.invert();
	//		break;

	//	default: break;
	//	}

	//	break;
	//}
	//case END:
	//{
	//	break;
	//}
	//case FLOW:
	//{
	//	switch( key )
	//	{
	//	case 'G':
	//	case 'g': toggleGuiDraw = !toggleGuiDraw; break;
	//	case 'f':
	//	case 'F': doFullScreen.set( !doFullScreen.get() ); break;
	//	case 'c':
	//	case 'C': doDrawCamBackground.set( !doDrawCamBackground.get() ); break;
	//	case 'e':
	//	case 'E': levelController.spawnEnemy = !levelController.spawnEnemy; break;

	//	case '1': drawMode.set( DRAW_COMPOSITE ); break;
	//	case '2': drawMode.set( DRAW_FLUID_FIELDS ); break;
	//	case '3': drawMode.set( DRAW_FLUID_VELOCITY ); break;
	//	case '4': drawMode.set( DRAW_FLUID_PRESSURE ); break;
	//	case '5': drawMode.set( DRAW_FLUID_TEMPERATURE ); break;
	//	case '6': drawMode.set( DRAW_OPTICAL_FLOW ); break;
	//	case '7': drawMode.set( DRAW_FLOW_MASK ); break;
	//	case '8': drawMode.set( DRAW_MOUSE ); break;

	//	case 'r':
	//	case 'R':
	//		fluidSimulation.reset();
	//		fluidSimulation.addObstacle( flowToolsLogoImage.getTexture() );
	//		inputForces.reset();
	//		break;

	//	case 'i':
	//	case 'I':
	//		fluidSimulation.invert();
	//		particleFlow.invert();
	//		break;

	//	default: break;
	//	}
	//	break;
	//}
	//default: break;
	//}
	//
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
#ifdef DEBUG_GL_ERRORS
    std::stringstream ss;
    ss << "GL Error 8 = " << glGetError() << std::endl;
    ofLogNotice(ss.str());
#endif // DEBUG_GL_ERRORS

    
	switch(gameState)
	{
	case START:
	{
		//startScreen.draw(0, 0);
#if !((TARGET_OS_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE) || (TARGET_IOS))
		splashHDImage.draw( 0, 0 );
#else
		splashiPadImage.draw( 0, 0 );
#endif

		break;
	}
	case GAME:
	{
		if( fluidSimulation.isInverted() )
			ofClear( 255, 255 );
		else
			ofClear( 0, 0 );

		//if( !toggleGuiDraw )
		//{
			//ofHideCursor();
			drawComposite();
		//}
//		else
//		{
//			ofShowCursor();
//			switch( drawMode.get() )
//			{
//			case DRAW_COMPOSITE: drawComposite(); break;
//			case DRAW_PARTICLES: drawParticles(); break;
//			case DRAW_FLUID_FIELDS: drawFluidFields(); break;
//			case DRAW_FLUID_DENSITY: drawFluidDensity(); break;
//			case DRAW_FLUID_VELOCITY: drawFluidVelocity(); break;
//			case DRAW_FLUID_PRESSURE: drawFluidPressure(); break;
//			case DRAW_FLUID_TEMPERATURE: drawFluidTemperature(); break;
//			case DRAW_FLUID_DIVERGENCE: drawFluidDivergence(); break;
//			case DRAW_FLUID_VORTICITY: drawFluidVorticity(); break;
//			case DRAW_FLUID_BUOYANCY: drawFluidBuoyance(); break;
//			case DRAW_FLUID_OBSTACLE: drawFluidObstacle(); break;
//			case DRAW_FLOW_MASK: drawMask(); break;
//			case DRAW_OPTICAL_FLOW: drawOpticalFlow(); break;
//			case DRAW_SOURCE: drawSource(); break;
//			case DRAW_MOUSE: drawMouseForces(); break;
//			case DRAW_VELDOTS: drawVelocityDots(); break;
//			}
//#if !((TARGET_OS_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE) || (TARGET_IOS))
//			drawGui();
//#endif
//		}

		//ofPushStyle();
		//ofEnableBlendMode( OF_BLENDMODE_ALPHA );
		////buttonsPanel.draw();
		//redButton.draw();
		//greenButton.draw();
		//blueButton.draw();

		//// HACK TO COMPENSATE FOR DISSAPEARING MOUSE
		//ofEnableBlendMode( OF_BLENDMODE_SUBTRACT );
		//ofDrawCircle( ofGetMouseX(), ofGetMouseY(), ofGetWindowWidth() / 300.0 );
		//ofEnableBlendMode( OF_BLENDMODE_ADD );
		//ofDrawCircle( ofGetMouseX(), ofGetMouseY(), ofGetWindowWidth() / 600.0 );
		//ofPopStyle();

		//player->get<inkSpriteComponent>()->draw();

		redInkwell->get<inkSpriteComponent>()->draw();
		blueInkwell->get<inkSpriteComponent>()->draw();
		greenInkwell->get<inkSpriteComponent>()->draw();

		//for(auto&& b : bullets)
		//{
		//	b->get<inkSpriteComponent>()->draw();
		//}

		//for(auto&& e : enemies)
		//{
		//	e->get<inkSpriteComponent>()->draw();
		//}

		//for( auto&& l : bonuses )
		//{
		//	l->get<inkSpriteComponent>()->draw();
		//}

		//for( int i = 0; i < lives; ++i )
		//{
		//	player->get<inkSpriteComponent>()->img->draw( ofGetWidth() - ( i * player->get<inkCharacterController>()->width ) - 100, 30 );
		//}

		//scoreFont.drawString( ofToString( score ), 30, 72 );

//		break;
//	}
//	case END:
//	{
//		endScreen.draw(0, 0);
//
//		float w = scoreFont.stringWidth( ofToString( score ) );
//		scoreFont.drawString( ofToString( score ), ofGetWidth() / 2 - w / 2, ofGetHeight() / 2 + 100 );
//
//		break;
//	}
//	case FLOW:
//	{
//		//glClearColor(0.3f, 0.4f, 0.1f, 1.0f);
//		//ofColor::white
//		//ofClear(ofColor(128,128,128,255));
//		if( fluidSimulation.isInverted() )
//			ofClear( 255, 255 );
//		else
//			ofClear( 0, 0 );
//		//ofBackground(ofColor::white);
//		//ofBackground(ofColor(255, 255, 255, 255));
//		if( doDrawCamBackground.get() )
//			drawSource();
//
//#ifdef DEBUG_GL_ERRORS
//        ss.clear();
//        ss << "GL Error 9 = " << glGetError() << std::endl;
//        ofLogNotice(ss.str());
//#endif // DEBUG_GL_ERRORS
//
//
//		if( !toggleGuiDraw )
//		{
//			//ofHideCursor();
//			drawComposite();
//		}
//		else
//		{
//			ofShowCursor();
//			switch( drawMode.get() )
//			{
//			case DRAW_COMPOSITE: drawComposite(); break;
//			case DRAW_PARTICLES: drawParticles(); break;
//			case DRAW_FLUID_FIELDS: drawFluidFields(); break;
//			case DRAW_FLUID_DENSITY: drawFluidDensity(); break;
//			case DRAW_FLUID_VELOCITY: drawFluidVelocity(); break;
//			case DRAW_FLUID_PRESSURE: drawFluidPressure(); break;
//			case DRAW_FLUID_TEMPERATURE: drawFluidTemperature(); break;
//			case DRAW_FLUID_DIVERGENCE: drawFluidDivergence(); break;
//			case DRAW_FLUID_VORTICITY: drawFluidVorticity(); break;
//			case DRAW_FLUID_BUOYANCY: drawFluidBuoyance(); break;
//			case DRAW_FLUID_OBSTACLE: drawFluidObstacle(); break;
//			case DRAW_FLOW_MASK: drawMask(); break;
//			case DRAW_OPTICAL_FLOW: drawOpticalFlow(); break;
//			case DRAW_SOURCE: drawSource(); break;
//			case DRAW_MOUSE: drawMouseForces(); break;
//			case DRAW_VELDOTS: drawVelocityDots(); break;
//			}
//#if !((TARGET_OS_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE) || (TARGET_IOS))
//			drawGui();
//#endif
//		}
//		break;
	}
	default:
		break;
	}
    
#ifdef DEBUG_GL_ERRORS
    ss.clear();
    ss << "GL Error 19 = " << glGetError() << std::endl;
    ofLogNotice(ss.str());
#endif // DEBUG_GL_ERRORS

}

//-------------------------------------------------------------------------------------------------
void inkApp::drawComposite( int _x, int _y, int _width, int _height )
{
#ifdef DEBUG_GL_ERRORS
    std::stringstream ss;
    ss << "GL Error 10 = " << glGetError() << std::endl;
    ofLogNotice(ss.str());
#endif // DEBUG_GL_ERRORS

    
	ofPushStyle();

	ofEnableBlendMode( OF_BLENDMODE_ALPHA );
	fluidSimulation.draw( _x, _y, _width, _height );
    
#ifdef DEBUG_GL_ERRORS
    ss.clear();
    ss << "GL Error 11 = " << glGetError() << std::endl;
    ofLogNotice(ss.str());
#endif // DEBUG_GL_ERRORS


	//ofEnableBlendMode( OF_BLENDMODE_ALPHA );
	//if( particleFlow.isActive() )
	//	particleFlow.draw( _x, _y, _width, _height );
    
#ifdef DEBUG_GL_ERRORS
    ss.clear();
    ss << "GL Error 17 = " << glGetError() << std::endl;
    ofLogNotice(ss.str());
#endif // DEBUG_GL_ERRORS


	//if( showLogo )
	//{
	//	flowToolsLogoImage.draw( _x, _y, _width, _height );
	//}

	ofPopStyle();
    
#ifdef DEBUG_GL_ERRORS
    ss.clear();
    ss << "GL Error 18 = " << glGetError() << std::endl;
    ofLogNotice(ss.str());
#endif // DEBUG_GL_ERRORS

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
	//ofPushStyle();
	//ofClear( 0, 0 );

	//for( int i = 0; i < inputForces.getNumForces(); i++ )
	//{
	//	ofEnableBlendMode( OF_BLENDMODE_ADD );
	//	if( inputForces.didChange( i ) )
	//	{
	//		ftDrawForceType dfType = inputForces.getType( i );
	//		if( dfType == FT_DENSITY )
	//			inputForces.getTextureReference( i )
	//			.draw( _x, _y, _width, _height );
	//	}
	//}

	//for( int i = 0; i < inputForces.getNumForces(); i++ )
	//{
	//	ofEnableBlendMode( OF_BLENDMODE_ALPHA );
	//	if( inputForces.didChange( i ) )
	//	{
	//		switch( inputForces.getType( i ) )
	//		{
	//		case FT_VELOCITY:
	//			velocityField.setVelocity( inputForces.getTextureReference( i ) );
	//			velocityField.draw( _x, _y, _width, _height );
	//			break;
	//		case FT_TEMPERATURE:
	//			temperatureField.setTemperature( inputForces
	//											 .getTextureReference( i ) );
	//			temperatureField.draw( _x, _y, _width, _height );
	//			break;
	//		case FT_PRESSURE:
	//			pressureField.setPressure( inputForces.getTextureReference( i ) );
	//			pressureField.draw( _x, _y, _width, _height );
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	//ofPopStyle();
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
	settingsPanel.draw();
	//buttonsPanel.draw();

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
	//switch( gameState )
	//{
	//case START:
	//{
	//	break;
	//}
	//case GAME:
	//{
	//	switch( key )
	//	{
	//	case 'w':
	//	case 'W':
	//	case OF_KEY_UP:
	//	{
	//		player->get<inkCharacterController>()->isUpPressed = false;
	//		break;
	//	}

	//	case 'a':
	//	case 'A':
	//	case OF_KEY_LEFT:
	//	{
	//		player->get<inkCharacterController>()->isLeftPressed = false;
	//		break;
	//	}

	//	case 's':
	//	case 'S':
	//	case OF_KEY_DOWN:
	//	{
	//		player->get<inkCharacterController>()->isDownPressed = false;
	//		break;
	//	}

	//	case 'd':
	//	case 'D':
	//	case OF_KEY_RIGHT:
	//	{
	//		player->get<inkCharacterController>()->isRightPressed = false;
	//		break;
	//	}

	//	default: break;
	//	}

	//	break;
	//}
	//case END:
	//{
	//	break;
	//}
	//case FLOW:
	//{
	//	break;
	//}
	//default: break;
	//}
}

void inkApp::touchMoved( int x, int y, int id)
{
	ofVec2f pos( x, y );
	float maxDist = 50000.f;
	float redDist = pos.distance( redInkwell->pos );
	float greenDist = pos.distance( greenInkwell->pos );
	float blueDist = pos.distance( blueInkwell->pos );

	if( ( inkColor == NO_COLOR || inkColor == RED ) && redDist < maxDist && redDist < greenDist && redDist < blueDist )
	{
		redInkwell->pos += ( pos - redInkwell->pos ) / 2.f;
		inkColor = RED;
	}
	else if( ( inkColor == NO_COLOR || inkColor == GREEN ) && greenDist < maxDist && greenDist < redDist && greenDist < blueDist )
	{
		greenInkwell->pos += ( pos - greenInkwell->pos ) / 2.f;
		inkColor = GREEN;
	}
	else if( ( inkColor == NO_COLOR || inkColor == BLUE ) && blueDist < maxDist && blueDist < greenDist && blueDist < redDist )
	{
		blueInkwell->pos += ( pos - blueInkwell->pos ) / 2.f;
		inkColor = BLUE;
	}
	else
	{
		inkColor = NO_COLOR;
	}
}

//-------------------------------------------------------------------------------------------------
void inkApp::mouseMoved( int x, int y )
{

}

//-------------------------------------------------------------------------------------------------
void inkApp::mouseDragged( int x, int y, int button )
{
	ofVec2f pos( x, y );
	float maxDist = 100.f;
	float redDist = pos.distance( redInkwell->pos );
	float greenDist = pos.distance( greenInkwell->pos );
	float blueDist = pos.distance( blueInkwell->pos );

	if( (inkColor == NO_COLOR || inkColor == RED) && redDist < maxDist && redDist < greenDist && redDist < blueDist )
	{
		redInkwell->pos += ( pos - redInkwell->pos ) / 2.f;
		inkColor = RED;
	}
	else if( ( inkColor == NO_COLOR || inkColor == GREEN ) && greenDist < maxDist && greenDist < redDist && greenDist < blueDist )
	{
		greenInkwell->pos += ( pos - greenInkwell->pos ) / 2.f;
		inkColor = GREEN;
	}
	else if( ( inkColor == NO_COLOR || inkColor == BLUE ) && blueDist < maxDist && blueDist < greenDist && blueDist < redDist )
	{
		blueInkwell->pos += ( pos - blueInkwell->pos ) / 2.f;
		inkColor = BLUE;
	}
	else
	{
		inkColor = NO_COLOR;
	}
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
