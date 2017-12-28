#include"Monster1Collision.h"
#include<math.h>
Monster1Collision::Monster1Collision(int stt, float x, float y, float width, float height, string tag, int mode) :
Collision(stt, x, y, width, height, tag)
{
	TargetIndex = stt;
	count = 0;
	leftRight = mode;
	_velocityX = 0.5;
	_velocityY = 0.5;
	vectorX = 1;
	vectorY = 0;
	centerX = x + width / 2;
	centerY = y + height / 2;
}

void Monster1Collision::OnCollisionEnter(string &tag)
{

}

void Monster1Collision::ImportTarget(int index)
{
	ActivateBrickIndex[count] = index;
	count++;
}
void Monster1Collision::Climb(int x, int y, int width, int height)
{
	centerX = _x + _width / 2;
	centerY = _y + _height / 2;
	int up = centerY - _height;
	int down = centerY + _height;
	int left = centerX - _width;
	int right = centerX + _width;
	//spriteState = 3;

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
int Monster1Collision::GetActiveArea(int index)
{
	return ActivateBrickIndex[index];
}

int Monster1Collision::getVX()
{
	return vectorX;
}
int Monster1Collision::getVY()
{
	return vectorY;
}
int Monster1Collision::getST()
{
	return spriteState;
}

Monster1Collision::~Monster1Collision()
{

}