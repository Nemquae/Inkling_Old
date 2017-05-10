#pragma once
#include "ofMain.h"

class inkFinger : ofTouchEventArgs
{
public:
	inkFinger(int id, float x, float y);
	inkFinger(ofTouchEventArgs & touch);
	~inkFinger();

	void update(ofTouchEventArgs &touch);

	int id;
	float x;
	float y;
	float accel;
	float angle;
	float prevX;
	float prevY;
};

