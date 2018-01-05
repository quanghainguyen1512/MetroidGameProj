#include"Monster2Collision.h"
#include<math.h>

Monster2Collision::Monster2Collision(int stt, float x, float y, float width, float height, string tag, int mode) :
MonsterCollision(stt, x, y, width, height, tag, mode)
{
	_velocityX = 4;
	_velocityY = 4;
	vectorX = 0;
	vectorY = 0;
	attack = false;
}

bool Monster2Collision::OnCollisionEnter(string &tag)
{
	if (tag == "bullet")
	{
		Active = true;
		Destroy = true;
	}
	return true;
}

void Monster2Collision::Orbit(int x, int y, int width, int height, int TargetX, int TargerY)
{
	centerX = _x + _width / 2;
	centerY = _y + _height / 2;

	Fall(x, y, width, height, TargetX, TargerY);
}

void Monster2Collision::Fall(int x, int y, int width, int height, int targetX, int targetY)
{
	if (sqrt(pow((_x - targetX), 2) + pow((_y - targetY), 2)) <= 175 && attack == false)
	{
		attack = true;
	}
	if (attack == true)
	{
		if (targetX > _x)
		{
			vectorX = 1;
		}
		else if (targetX < _x)
		{
			vectorX = -1;
		}
		else
		{
			vectorX = 0;
		}
		vectorY = 1;
		if (_y + _height >= y)
		{
			vectorX = 0;
			vectorY = 0;
			timeCount++;
			if (timeCount > 5)
			{
				Active = false;
			}
		}
	}
	_velocityX = abs(_velocityX)*vectorX;
	_velocityY = abs(_velocityY)*vectorY;
}

int Monster2Collision::getST()
{
	if (Destroy == true)
	{
		return -1;
	}
	if (attack == true)
		return 1;
	else
		return 0;
}


Monster2Collision::~Monster2Collision()
{

}