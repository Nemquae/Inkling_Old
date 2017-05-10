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

#include "inkComponent.h"

namespace ink
{

class inkCharacterController :
	public inkComponent
{
public:
	inkCharacterController( inkGameObject & gameObj );
	virtual ~inkCharacterController();

	float width, height, speed;
	int collisionLayer;
	int lifeTime;
	int fingerIndex;

	bool isLeftPressed, isRightPressed, isDownPressed, isUpPressed;

	void setup() override;
	void update() override;

	void calculateMovement();
};	//	inkCharacterController

}	//	ink

