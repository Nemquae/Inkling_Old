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
#include <utility>
#include <stdexcept>
#include <exception>
#include <iostream>

#include "inkGameObject.h"

using namespace std;

namespace ink
{

class inkGameObjectFactory
{
public:
	inkGameObjectFactory();

	virtual ~inkGameObjectFactory();

	enum PrefabType
	{
		PLAYER
	,	ENEMY
	,	BULLET
	,	LIFE
	};

	template<class...Args>
	shared_ptr<inkGameObject> create( const PrefabType& type, Args&&...args );



private:

	template<class T, class...Args>
	class creatable_from;

	template<class T, class...Args>
	static auto createEmpty( Args&&...args )
		->enable_if_t< creatable_from<T, Args...>::value, shared_ptr<T> >;

	template<class T, class...Args>
	static auto createEmpty( Args&&...args )
		->enable_if_t< !creatable_from<T, Args...>::value, shared_ptr<T> >;


};	//	EntityFactory

}	//	ink
