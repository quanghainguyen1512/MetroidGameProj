#include"Monster1Collision.h"
#include<math.h>
Monster1Collision::Monster1Collision(int stt, float x, float y, float width, float height, string tag, int mode) :
MonsterCollision(stt, x, y, width, height, tag, mode)
{
	leftRight = mode;
	_velocityX = 1;
	_velocityY = 1;
	vectorX = 1;
	vectorY = 0;
	spriteState = 3;
}

bool Monster1Collision::OnCollisionEnter(string &tag)
{
	if (tag == "bullet")
	{
		Active = true;
		Destroy = true;
	}
	return true;
}

void Monster1Collision::Orbit(int x, int y, int width, int height, int TargetX, int TargerY)
{
	centerX = _x + _width / 2;
	centerY = _y + _height / 2;

	Climb(x, y, width, height);

}

void Monster1Collision::Climb(int x, int y, int width, int height)
{
	int up = centerY - _height;
	int down = centerY + _height;
	int left = centerX - _width;
	int right = centerX + _width;

	if (leftRight == false)
	{
		if (_y <= y - _height)
		{
			_y = y - _height;
		}
		if (_x >= x + width)
		{
			_x = x + width;
		}
		if (_y >= y + height)
		{
			_y = y + height;
		}
		if (_x <= x - _width)
		{
			_x = x - _width;
		}

		if (_y <= y - _height&&_x == x + width)
		{
			_y = y - _height + 1;
			vectorX = 0;
			vectorY = 1;
			spriteState = 0;
		}
		if (_y == y + height&&_x >= x + width)
		{
			_x = x + width - 1;
			vectorX = -1;
			vectorY = 0;
			spriteState = 1;
		}
		if (_y >= y + height&&_x == x - _width)
		{
			_y = y + height - 1;
			vectorX = 0;
			vectorY = -1;
			spriteState = 2;
		}
		if (_y == y - _height&&_x <= x - _width)
		{
			x = x - _width + 1;
			vectorX = 1;
			vectorY = 0;
			spriteState = 3;
		}
	}
	else
	{
		if (x + 8 >= left)
		{
			vectorY = 0;
			vectorX = 1;
		}
		else if (right >= x + width + 8)
		{
			vectorY = 0;
			vectorX = -1;
		}
		spriteState = 3;
	}

	_velocityX = abs(_velocityX) *vectorX;
	_velocityY = abs(_velocityY)*vectorY;
}

int Monster1Collision::getST()
{
	if (Destroy == true)
	{
		return -1;
	}
	if (_tag == "monster1")
		return spriteState;
}

Monster1Collision::~Monster1Collision()
{

}