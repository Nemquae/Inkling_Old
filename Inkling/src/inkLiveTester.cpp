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

#include "inkLiveTester.h"


using namespace ink;

inkLiveTester::inkLiveTester()
{
}


inkLiveTester::~inkLiveTester()
{
}

void inkLiveTester::setup()
{
	// address of iOS/Android device
	sender.setup( "XXX.XXX.XXX.XXX", 8000 );

	// port the game will receive on, make sure to set on mobile device
	receiver.setup( 8001 );

	m.setAddress( "/game" );
}

void inkLiveTester::update()
{
	while(receiver.hasWaitingMessages())
	{
		ofxOscMessage m;

		receiver.getNextMessage( &m );

		ofxOscMessage sendBack;

		if(m.getAddress() == "/game/maxEnemyAmplitude")
		{
			maxEnemyAmplitude = m.getArgAsFloat( 0 );
			sendBack.addFloatArg( maxEnemyAmplitude );
			sendBack.setAddress( "/updatedVals/maxEnemyAmplitude" );
			sender.sendMessage( sendBack );

			ofLogNotice() << maxEnemyAmplitude << std::endl;
		}
		else if(m.getAddress() == "/game/enemyIntervalTime")
		{
			enemyIntervalTime = m.getArgAsInt32( 0 );
			sendBack.addIntArg( enemyIntervalTime );
			sendBack.setAddress( "/updatedVals/enemyIntervalTime" );
			sender.sendMessage( sendBack );

			ofLogNotice() << enemyIntervalTime << std::endl;
		}
		else if(m.getAddress() == "/game/maxEnemyShootInterval")
		{
			maxEnemyShootInterval = m.getArgAsFloat( 0 );
			sendBack.addFloatArg( maxEnemyShootInterval );
			sendBack.setAddress( "/updatedVals/maxEnemyShootInterval" );
			sender.sendMessage( sendBack );

			ofLogNotice() << maxEnemyShootInterval << std::endl;
		}
		else if(m.getAddress() == "/game/triggerBonus")
		{
			triggerBonus = m.getArgAsInt32( 0 );
			sendBack.addIntArg( triggerBonus );
			sendBack.setAddress( "/updatedVals/triggerBonus" );
			sender.sendMessage( sendBack );

			ofLogNotice() << triggerBonus << std::endl;
		}
	}
}
