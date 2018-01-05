#include"DoorCollsiion.h"

DoorCollision::DoorCollision(int stt, float x, float y, float width, float height, string tag, int mode) :
Collision(stt, x, y, width, height, tag)
{
	LeftDestroy = false;
	RightDestroy = false;
	GetThrough = false;
	_mode = mode;

	brickIndex = -1;
	
}

void DoorCollision::ImportTarget(int B)
{
	brickIndex = B;
}

bool DoorCollision::OnCollisionEnter(string &tag)
{
	if (tag == "left")
	{
		LeftDestroy = true;
		GetThrough = true;

	}
	if (tag == "right")
	{
		RightDestroy = true;
		GetThrough = true;

	}
    if (tag == "player")
	{
		Active = false;
	}
	return true;
}

int DoorCollision::getST()
{
	if (LeftDestroy == true)
		return 1;
	else if (RightDestroy == true)
		return 2;
	return 0;
}

bool DoorCollision::getLeft()
{
	return LeftDestroy;
}

bool DoorCollision::getRight()
{
	return RightDestroy;
}

void DoorCollision::setActive(bool a)
{
	Active = a;
}
int DoorCollision::getMode()
{
	return _mode;
}

void DoorCollision::reset()
{
	Active = true;
	GetThrough = false;
	LeftDestroy = false;
	RightDestroy = false;
}

DoorCollision::~DoorCollision()
{

}