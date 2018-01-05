#include"Monster4Collision.h"
#include<math.h>
Monster4Collision::Monster4Collision(int stt, float x, float y, float width, float height, string tag, int mode) :
MonsterCollision(stt, x, y, width, height, tag, mode)
{


	_velocityX = 1;
	_velocityY = 3;
	vectorX = 0;
	vectorY = 0;
	attack = false;

}

bool Monster4Collision::OnCollisionEnter(string &tag)
{

	if (tag == "bullet")
	{
		Active = true;
		Destroy = true;
	}

	return true;
}

void Monster4Collision::Orbit(int x, int y, int width, int height, int TargetX, int TargerY)
{
	centerX = _x + _width / 2;
	centerY = _y + _height / 2;
	
	Infinity(x, y, width, height, TargetX, TargerY);
	 
}

 
void Monster4Collision::Infinity(int x, int y, int width, int height, int targetX, int targetY)
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
			_y = y - _height;
			vectorY = 0;
			timeCount++;
			if (timeCount % 10 == 0)
			{
				vectorY = -1;
			}
		}
		else if (vectorY == -1 && _y <= startY)
		{
			_y = startY;
			vectorY = 0;
			timeCount++;
			if (timeCount % 10 == 0)
			{
				vectorY = 1;
			}
		}
	}
	_velocityX = abs(_velocityX)*vectorX;
	_velocityY = abs(_velocityY)*vectorY;
}
int Monster4Collision::getST()
{
	if (Destroy == true)
	{
		return -1;
	}
}
Monster4Collision::~Monster4Collision()
{

}