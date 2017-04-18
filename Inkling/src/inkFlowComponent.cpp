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


inkFlowComponent::inkFlowComponent( inkGameObject & gameObj )
: inkComponent( gameObj )
{
}


inkFlowComponent::~inkFlowComponent()
{
}

void inkFlowComponent::setup()
{
	drawDensityForce.setup( ofGetWidth(), ofGetHeight(), FT_DENSITY, true );
	drawDensityForce.setName( "draw full res" );
	drawDensityForce.setForce( ofColor( 255.f, 0.f, 0.f ) );
	drawDensityForce.setStrength( 100.f );
	drawVelocityForce.setup( ofGetWidth()/4, ofGetHeight()/4, FT_VELOCITY, true );
	drawVelocityForce.setName( "draw flow res 1" );
	drawTemperatureForce.setup( ofGetWidth()/4, ofGetHeight()/4, FT_TEMPERATURE, true );
	drawTemperatureForce.setName( "draw flow res 2" );

	lastPos = gameObject.pos;
}

void inkFlowComponent::update()
{
	ofVec2f velocity = ofVec2f(gameObject.pos.x - lastPos.x, gameObject.pos.y - lastPos.y);
	lastPos = gameObject.pos;

	drawDensityForce.applyForce( velocity );
	drawVelocityForce.setForce( velocity );
	drawTemperatureForce.applyForce( velocity );

	drawDensityForce.update();
	drawVelocityForce.update();
	drawTemperatureForce.update();
}

void inkFlowComponent::draw()
{
	
}

void inkFlowComponent::reset()
{
	drawDensityForce.reset();
	drawVelocityForce.reset();
	drawTemperatureForce.reset();
}