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
#include <unordered_map>
#include <typeindex>

#include "ofPoint.h"
#include "inkXMacros.h"
#include "inkComponent.h"

namespace ink
{

class inkGameObject
{
public:

	inkGameObject();
	virtual ~inkGameObject();

	ofPoint		pos;
	const int	id;

	static int	totalIDs;

	void update();

	template <typename T>
	std::shared_ptr<T> get(int id = 0)
	{
		std::type_index index( typeid( T ) );
		if(components.count(std::type_index(typeid(T))) != 0)
		{
			std::unordered_map< int, std::shared_ptr<inkComponent> > & map = components[ index ];
			
			if( map.count( id ) != 0 )
			{
				return static_pointer_cast<T>( map[ id ] );
			}
			else if( id == 0 && map.size() > 0 )
			{
				return static_pointer_cast<T>( map.begin()->second );
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			return nullptr;
		}
	}

	template <typename T>
	void add(std::shared_ptr< T> component)
	{
		components[ std::type_index( typeid( *component ) ) ][component->id] = component;
	}

	template <typename T>
	void add()
	{
		std::shared_ptr<inkComponent> component = 
			static_pointer_cast<inkComponent>( std::make_shared<T>(*this) );

		components[ std::type_index( typeid( T ) ) ][ component->id ] = component;
	}

private:

	std::unordered_map<std::type_index, std::unordered_map< int, std::shared_ptr<inkComponent> > > 
		components;

};	//	inkGameObject

}	//	ink

