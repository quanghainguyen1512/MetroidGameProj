#include"Monster3Collision.h"
#include<math.h>
Monster3Collision::Monster3Collision(int stt, float x, float y, float width, float height, string tag, int mode) :
MonsterCollision(stt, x, y, width, height, tag, mode)
{
	_velocityX = 2;
	_velocityY = 0;
	vectorX = 1;
	vectorY = 0;
	minX = mode * 16;
	maxX = mode * 16;
}

bool Monster3Collision::OnCollisionEnter(string &tag)
{
	return true;
}

void Monster3Collision::Orbit(int x, int y, int width, int height, int TargetX, int TargerY)
{
	centerX = _x + _width / 2;
	centerY = _y + _height / 2;
	
	LeftRight(x, y, width, height);

}
 
void Monster3Collision::LeftRight(int x, int y, int width, int height)
{
	if (_x <= minX)
	{
		vectorX = 1;
	}
	else if (_x + _width >= maxX)
	{
		vectorX = -1;
	}
	_velocityX = abs(_velocityX)*vectorX;
	_velocityY = abs(_velocityY)*vectorY;
}
 

int Monster3Collision::getST()
{
	if (Destroy == true)
	{
		return -1;
	}
	return 0;
}

void Monster3Collision::SetLimitation(int x, int y, int width, int height)
{
	if (x > minX)
	{
		maxX = x;
	}
	else if (x + width < minX)
	{
		maxX = minX;
		minX = x + width;
	}
}

Monster3Collision::~Monster3Collision()
{

}