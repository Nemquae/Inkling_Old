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

#include "inkCharacterController.h"
#include "inkGameObject.h"

using namespace ink;

inkCharacterController::inkCharacterController( inkGameObject & gameObj )
: inkComponent(gameObj)
{
}


inkCharacterController::~inkCharacterController()
{
}

void inkCharacterController::setup()
{
	width = 0;
	height = 0;
	speed = 1;
	isLeftPressed = false;
	isRightPressed = false;
	isUpPressed = false;
	isDownPressed = false;
}

void inkCharacterController::update()
{
	this->calculateMovement();
}

void inkCharacterController::calculateMovement()
{
	if(isLeftPressed)
	{
		gameObject.pos.x -= speed;
	}
	if(isRightPressed)
	{
		gameObject.pos.x += speed;
	}
	if(isUpPressed)
	{
		gameObject.pos.y -= speed;
	}
	if(isDownPressed)
	{
		gameObject.pos.y += speed;
	}
}