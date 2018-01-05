#include"Collision.h"

using namespace std;

Collision::Collision(int stt,float x, float y, float width, float height, string tag)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_tag = tag;
	_stt = stt;

	centerX = x + width / 2;
	centerY = y + height / 2;
	startX = x;
	startY = y;
	Active = true;
}

void Collision::Update(float x, float y, float width, float height, float velocityx, float velocityy)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_velocityX = velocityx;
	_velocityY = velocityy;

	centerX = (_x + (_x + _width)) / 2;
	centerY = (_y + (_y + _height)) / 2;
}

//normalx va normaly su dung cho cac kieu va cham khac nhu phan xa hay truot
float Collision::SweptAABB(Collision* P, float &normalx, float &normaly)
{
	//tinh khoang cach giua 2 collision
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	if (P->_velocityX > 0.0f)
	{
		xInvEntry = _x - (P->_x + P->_width);
		xInvExit = (_x + _width) - P->_x;
	}
	else
	{
		xInvEntry = (P->_x + P->_width) - _x;
		xInvExit = _x - (P->_x + P->_width);
	}

	if (P->_velocityY > 0.0f)
	{
		yInvEntry = _y - (P->_y + P->_height);
		yInvExit = (_y + _height) - P->_y;
	}
	else
	{
		yInvEntry = (_y + _height) - P->_y;
		yInvExit = _y - (P->_y + P->_height);
	}

	// tinh thoi gian 2 collision cham nhau hay ra khoi nhau
	float xEntry, yEntry;
	float xExit, yExit;
	if (P->_velocityX == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / P->_velocityX;
		xExit = xInvExit / P->_velocityX;
	}
	if (P->_velocityY == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / P->_velocityY;
		yExit = yInvExit / P->_velocityY;
	}

	// tim thoi gian lon nhat khi 2 collision thoat khoi nhau,thoi gian nho nhat khi 2 collisoin cham nhau
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// kiem tra co collision
	//neu khong collision tra ve 1
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // neu co collision
	{
		// tinh x va y khi collision
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}
		// tra ve thoi gian va cham
		return entryTime;
	}
}

float Collision::YCollisionTime(float y0, float height, Collision* P, float VelocityY)
{
	if (P->_x < _x + _velocityX&&_x + _velocityX < P->_x + P->_width ||
		P->_x < _x + _width + _velocityX&&_x + _width + _velocityX < P->_x + P->_width ||
		_x + _velocityX < P->_x&&P->_x < _x + _width + _velocityX)
	{
		enter = true;
		if (VelocityY > 0)
		{
			if (y0 + height <= _y + _velocityY&&_y + _velocityY < P->_y + P->_height)
			{
				enterTimeY = (P->_y + P->_height - (_y + _velocityY)) / VelocityY;
				return enterTimeY;
			}
		}
		else if (VelocityY < 0)
		{
			if (P->_y < _y + _height + _velocityY&&_y + _height + _velocityY <= y0)
			{
				enterTimeY = (P->_y - (_height + _y + _velocityY)) / (VelocityY);
				return enterTimeY;
			}
		}
	}
	return 0;
}

float Collision::XCollisionTime(float x0, float width, Collision* P, float VelocityX)
{
	if (P->_y < _y + _velocityY&&_y + _velocityY < P->_y + P->_height ||
		P->_y < _y + _height + _velocityY &&_y + _height + _velocityY < P->_y + P->_height ||
		_y + _velocityY < P->_y && P->_y < _y + _height + _velocityY)
	{
		enter = true;
		if (VelocityX > 0)
		{
			if (x0 + width <= _x + _velocityX && _x + _velocityX < P->_x + P->_width)
			{
				enterTimeX = ((P->_x + P->_width) - (_x + _velocityX)) / (VelocityX);
				return enterTimeX;
			}
		}
		else if (VelocityX < 0)
		{
			if (P->_x < _x + _width + _velocityX && _x + _width + _velocityX <= x0)
			{
				enterTimeX=((_x + _width + _velocityX) - P->_x) / (-VelocityX);
				return enterTimeX;
			}
		}
	}
	return 0;
}

bool Collision::OnCollisionEnter(string &tag)
{
	return false;
}

string Collision::getTag()
{
	return _tag;
}

int Collision::getX()
{
	return _x;
}
int Collision::getY()
{
	return _y;
}
int Collision::getHeight()
{
	return _height;
}
int Collision::getWidth()
{
	return _width;
}
void Collision::ImportTarget(int target){}

void Collision::reset()
{
	enterTimeX = 0;
	enterTimeY = 0;
	enter = false;
}

Collision::~Collision()
{

}