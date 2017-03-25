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

#include "inkGameObject.h"
#include "inkCharacterController.h"
#include "inkDefenseComponent.h"
#include "inkOffenseComponent.h"
#include "inkSpriteComponent.h"

namespace ink
{

enum PrefabType
{
	  PLAYER
	, ENEMY
	, BULLET
	, LIFE
};

template<class T, class...Args>
class creatable_from
{
public:
	template<class X, class...Ys>
	static auto test( int ) -> decltype( X( declval<Ys>()... ), void(), true_type() );

	template<class X, class...Ys>
	static auto test( ... ) -> decltype( false_type() );

	static constexpr auto value = decltype( test<T, Args...>( 0 ) )::value;

};

class inkGameObjectFactory
{
public:
	inkGameObjectFactory() {}

	virtual ~inkGameObjectFactory() {}

	template<class...Args>
	std::shared_ptr<inkGameObject> create( const PrefabType& type, Args&&...args )
	{
		shared_ptr<inkGameObject> gameObj = nullptr;

		switch( type )
		{
		case PLAYER:
			gameObj = createEmpty<inkGameObject>( forward<Args>( args )... );
			gameObj->add<inkCharacterController>();
			gameObj->add<inkDefenseComponent>();
			gameObj->add<inkOffenseComponent>();
			gameObj->add<inkSpriteComponent>();
			gameObj->setup();
			break;
		case ENEMY:
			gameObj = createEmpty<inkGameObject>( forward<Args>( args )... );
			gameObj->add<inkCharacterController>();
			gameObj->add<inkDefenseComponent>();
			gameObj->add<inkOffenseComponent>();
			gameObj->add<inkSpriteComponent>();
			gameObj->setup();
			break;
		case BULLET:
			gameObj = createEmpty<inkGameObject>( forward<Args>( args )... );
			gameObj->add<inkCharacterController>();
			gameObj->add<inkSpriteComponent>();
			gameObj->setup();
			break;
		case LIFE:
			break;
		default:
			break;
		}

		return gameObj;
	}

private:

	template<class T, class...Args>
	static auto createEmpty( Args&&...args )
		->std::enable_if_t< creatable_from<T, Args...>::value, std::shared_ptr<T> >
	{
		return make_shared<T>( forward<Args>( args )... );
	}

	template<class T, class...Args>
	static auto createEmpty( Args&&...args )
		->std::enable_if_t< !creatable_from<T, Args...>::value, std::shared_ptr<T> >
	{
		throw invalid_argument( "wrong number of arguments" );
	}


};	//	inkEntityFactory

}	//	ink
