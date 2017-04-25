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

#include "inkFlowComponent.h"
#include "inkGameObject.h"
#include "inkCharacterController.h"

using namespace ink;
using namespace flowTools;

bool inkFlowComponent::isInitialized = false;
ftDrawForceShader	inkFlowComponent::densityDrawForceShader;
ftFbo				inkFlowComponent::densityBuffer;
ftDrawForceShader	inkFlowComponent::velocityDrawForceShader;
ftFbo				inkFlowComponent::velocityBuffer;
ftDrawForceShader	inkFlowComponent::temperatureDrawForceShader;
ftFbo				inkFlowComponent::temperatureBuffer;

inkFlowComponent::inkFlowComponent( inkGameObject & gameObj )
: inkComponent( gameObj )
{
}


inkFlowComponent::~inkFlowComponent()
{
}

void inkFlowComponent::setup()
{
	parameters.setName( "flow force" );
	parameters.add( force.set( "force", ofVec4f( 1, 1, 1, 1 ), ofVec4f( -1, -1, -1, -1 ), ofVec4f( 1, 1, 1, 1 ) ) );
	parameters.add( strength.set( "strength", 1.0, 0, 5 ) );
	parameters.add( radius.set( "radius", 0.035, 0, .1 ) );
	parameters.add( edge.set( "edge", 1.0, 0, 1 ) );

	lastPos = gameObject.pos;

	if(!isInitialized)
	{
		isInitialized = true;
		densityDrawForceShader.setup();
		velocityDrawForceShader.setup();
		temperatureDrawForceShader.setup();

#if (TARGET_OS_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE) || (TARGET_IOS)
		densityBuffer.allocate( width, height, GL_RGBA );
		velocityBuffer.allocate( width, height, GL_RGBA );
		temperatureBuffer.allocate( width, height, GL_RGBA );
#else
		densityBuffer.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA32F );
		velocityBuffer.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA32F );
		temperatureBuffer.allocate( ofGetWidth(), ofGetHeight(), GL_RGBA32F );
#endif
		densityBuffer.black();
		velocityBuffer.black();
		temperatureBuffer.black();
	}

	density = ofFloatColor( 1, 1, 1, 1 );
	velocity = ofVec2f( 0, 0 );
	temperature = 1;
	pressure = -1;
	obstacle = true;

	forceChanged = false;
	forceApplied = false;

}

void inkFlowComponent::update()
{

	float width = gameObject.get<inkCharacterController>()->width;
	float height = gameObject.get<inkCharacterController>()->height;

	ofVec4f velocity = ofVec4f(-(gameObject.pos.x - lastPos.x)/4.f, -(gameObject.pos.y - lastPos.y)/4.f, 0, 1);
	ofVec2f normalizedPos = ofVec4f( (gameObject.pos.x + width/2.f) / ofGetWidth(), (gameObject.pos.y + height/2.f) / ofGetHeight(), 0, 1 );

	lastPos = gameObject.pos;

	absolutePosition = normalizedPos * ofVec2f( ofGetWidth(), ofGetHeight() );
	absoluteRadius = radius * ofGetWidth();


	ofVec4f velocityForce = force.get() * ofVec4f( ofGetWidth(), ofGetHeight(), 0, 1 );
	ofVec4f pressureForce = force.get() * ofVec4f( 100, 0, 0, 1 );
	ofVec4f temperatureForce = ofVec4f( force.get().x, force.get().x, force.get().x, 1 );
	ofVec4f obstacleForce = ofVec4f( force.get().x, force.get().x, force.get().x, 1 );

	ofPushStyle();

	ofEnableBlendMode( OF_BLENDMODE_ADD );

	densityDrawForceShader.update(		densityBuffer,
										force.get(),
										absolutePosition,
										absoluteRadius,
										edge,
										1.0f );

	velocityDrawForceShader.update(		velocityBuffer,
										velocity,
										absolutePosition,
										absoluteRadius,
										edge,
										0.0f );

	temperatureDrawForceShader.update(	temperatureBuffer,
										force.get(),
										absolutePosition,
										absoluteRadius,
										edge,
										0.0f );

	ofPopStyle();
}


void inkFlowComponent::reset()
{
	densityBuffer.black();
	velocityBuffer.black();
	temperatureBuffer.black();
}