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

#include "ofUtils.h"
#include "inkController.h"

namespace ink
{

class inkLevelController :
	public inkController
{
public:
	inkLevelController();
	virtual ~inkLevelController();

	float enemyStartTime;
	float enemyIntervalTime;

	float bonusStartTime;
	float bonusIntervalTime;

	void setup( float s );
	bool shouldSpawnEnemy();
	bool shouldSpawnBonus();

};	//	inkLevelController

}	//	ink

