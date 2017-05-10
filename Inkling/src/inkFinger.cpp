#include "inkFinger.h"



inkFinger::inkFinger(int _id, float _x, float _y)
{
	id = _id;
	x = _x;
	y = _y;

	prevX = x;
	prevY = y;
	accel = 0;
	angle = 0;
}

inkFinger::inkFinger(ofTouchEventArgs &touch)
{
	id = touch.id;
	x = touch.x;
	y = touch.y;

	prevX = x;
	prevY = y;
	accel = 0;
	angle = 0;
}

void inkFinger::update(ofTouchEventArgs &touch)
{
	x = touch.x;
	y = touch.y;
	accel = ofDist(prevX, prevY, x, y);
	angle = atan2(prevY - y, prevX - x) + PI;
	prevX = x;
	prevY = y;
}

inkFinger::~inkFinger()
{
}
