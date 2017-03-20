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

#include "inkGameObjectFactory.h"

#include <utility>
#include <stdexcept>
#include <exception>

using namespace ink;
using namespace std;

inkGameObjectFactory::inkGameObjectFactory()
{
}


inkGameObjectFactory::~inkGameObjectFactory()
{
}


template<class T, class...Args>
class inkGameObjectFactory::creatable_from
{
public:
	template<class X, class...Ys>
	static auto test( int ) -> decltype( X( declval<Ys>()... ), void(), true_type() );

	template<class X, class...Ys>
	static auto test( ... ) -> decltype( false_type() );

	static constexpr auto value = decltype( test<T, Args...>( 0 ) )::value;

};


template<class...Args>
std::shared_ptr<inkGameObject> inkGameObjectFactory::create(const inkGameObjectFactory::PrefabType&type, Args&&...args)
{
	shared_ptr<inkGameObject> entity;

	switch(type)
	{
	case Player:
		entity = createEmpty<inkGameObject>( forward<Args>( args )... );
		break;
	case Enemy:
		break;
	case Bullet:
		break;
	case Life:
		break;
	default:
		break;
	}

	return{};
}

template<class T, class...Args>
static auto inkGameObjectFactory::createEmpty(Args&&...args)
-> enable_if_t< creatable_from<T, Args...>::value, shared_ptr<T> >
{
	return make_shared<T>( forward<Args>( args )... );
}

template<class T, class...Args>
static auto inkGameObjectFactory::createEmpty(Args&&...args)
-> enable_if_t< ! creatable_from<T, Args...>::value, shared_ptr<T> >
{
	throw invalid_argument( "wrong number of arguments" );
}


