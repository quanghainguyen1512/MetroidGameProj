#include"Monster1Collision.h"
#include<math.h>
Monster1Collision::Monster1Collision(int stt, float x, float y, float width, float height, string tag, int mode) :
Collision(stt, x, y, width, height, tag)
{
	TargetIndex = stt;
	count = 0;
	Active = true;
	if (tag == "monster1")
	{
		leftRight = mode;
		_velocityX = 1;
		_velocityY = 1;
		vectorX = 1;
		vectorY = 0;
		spriteState = 3;
	}
	else if (tag == "monster2")
	{
		_velocityX = 4;
		_velocityY = 4;
		vectorX = 0;
		vectorY = 0;
		attack = false;
	}
	else if (tag == "monster3")
	{
		_velocityX = 2;
		_velocityY = 0;
		vectorX = 1;
		vectorY = 0;
		minX = mode * 16;
		maxX = mode * 16;
	}
}

bool Monster1Collision::OnCollisionEnter(string &tag)
{
	if (enter == true)
	{
		if (tag == "bullet")
		{
			Active = false;
		}
	}
	return enter;
}

void Monster1Collision::ImportTarget(int index)
{
	ActivateBrickIndex[count] = index;
	count++;
}

void Monster1Collision::Orbit(int x, int y, int width, int height, int TargetX, int TargerY)
{
	centerX = _x + _width / 2;
	centerY = _y + _height / 2;
	if (_tag == "monster1")
	{
		Climb(x, y, width, height);
	}
	else if (_tag == "monster2")
	{
		Fall(x, y, width, height, TargetX, TargetX);
	}
	else if (_tag == "monster3")
	{
		LeftRight(x, y, width, height);
	}
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

void Monster1Collision::Fall(int x, int y, int width, int height, int targetX, int targetY)
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

void Monster1Collision::LeftRight(int x, int y, int width, int height)
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
	if (_tag == "monster1")
		return spriteState;
	if (_tag == "monster2"&&attack == true)
		return 1;
	else
		return 0;

}

void Monster1Collision::SetLimitation(int x, int y, int width, int height)
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

Monster1Collision::~Monster1Collision()
{

}