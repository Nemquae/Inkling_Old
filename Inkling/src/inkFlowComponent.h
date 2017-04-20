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

#include <memory>

#include "inkComponent.h"
#include "ofMain.h"
#include "ftFbo.h"
#include "ftDrawForceShader.h"

namespace ink
{

enum inkFlowType
{
	INK_NONE = 0,
	INK_DENSITY = 1,
	INK_VELOCITY = 2,
	INK_TEMPERATURE = 3,
	INK_PRESSURE = 4,
	INK_OBSTACLE = 5,
};

class inkFlowComponent :
	public inkComponent
{
public:
	inkFlowComponent( inkGameObject & gameObj );
	virtual ~inkFlowComponent();

	virtual void setup() override;
	virtual void update() override;
	static void reset();

	void setName( string _name ) { parameters.setName( _name ); }
	void setRadius( float _radius ) { radius.set( _radius ); }
	void setEdge( float _edge ) { edge.set( _edge ); }
	void setStrength( float _strength ) { strength = _strength;}
	void setForce( float _force ) { force = ofVec4f( _force, 0.0, 0.0, 1.0 ); }
	void setForce( ofVec2f _force ) { force = ofVec4f( _force.x, _force.y, 0.0, 1.0 ); }
	void setForce( ofVec3f _force ) { force = ofVec4f( _force.x, _force.y, _force.z, 1.0 ); }
	void setForce( ofVec4f _force ) { force = ofVec4f( _force.x, _force.y, _force.z, _force.w ); }
	void setForce( ofFloatColor _force ) { force = ofVec4f( _force.r, _force.g, _force.b, _force.a ); }
	void setForce( ofColor _force ) { force = ofVec4f( _force.r / 255.0, _force.g / 255.0, _force.b / 255.0, _force.a / 255.0 ); }

	void setInitiatlPos( ofPoint _pos ) { lastPos = _pos; }

	float	getRadius() { return radius.get(); }
	float	getEdge() { return edge.get(); }
	float	getStrength() { return strength.get(); }
	ofVec4f	getForce() { return force.get(); }
	bool	didChange() { return forceChanged; }

	ofTexture & getDensityTexture() { return densityBuffer.getTexture(); }
	ofTexture & getVelocityTexture() { return velocityBuffer.getTexture(); }
	ofTexture & getTemperatureTexture() { return temperatureBuffer.getTexture(); }

	ofParameterGroup	parameters;

private:

	static bool							isInitialized;
	static flowTools::ftDrawForceShader	densityDrawForceShader;
	static flowTools::ftFbo				densityBuffer;
	static flowTools::ftDrawForceShader	velocityDrawForceShader;
	static flowTools::ftFbo				velocityBuffer;
	static flowTools::ftDrawForceShader	temperatureDrawForceShader;
	static flowTools::ftFbo				temperatureBuffer;

	ofParameter<ofVec4f> force;
	ofParameter<float>	strength;
	ofParameter<float>	radius;
	ofParameter<float>	edge;

	ofParameter<ofFloatColor>	density;
	ofParameter<ofVec2f>		velocity;
	ofParameter<float>			temperature;
	ofParameter<float>			pressure;
	ofParameter<bool>			obstacle;

	ofPoint lastPos;

	ofVec2f	absolutePosition;
	float	absoluteRadius;

	bool forceChanged;
	bool forceApplied;

};	//	inkFlowComponent

}// ink