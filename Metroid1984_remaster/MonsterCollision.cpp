#include"MonsterCollision.h"

MonsterCollision::MonsterCollision(int stt, float x, float y, float width, float height, string tag, int mode) :
Collision(stt, x, y, width, height, tag)
{
	TargetIndex = stt;
	count = 0;
	Active = true;
	Destroy = false;

	minX = 0;
	maxX = 0;
	vectorX = 0;
	vectorY = 0;
	spriteState = 0;
}

bool MonsterCollision::OnCollisionEnter(string &tag)
{
	return true;
}

void MonsterCollision::Orbit(int x, int y, int width, int height, int TargetX, int TargerY)
{

}
int MonsterCollision::GetActiveArea(int index)
{
	return ActivateBrickIndex[index];
}


int MonsterCollision::getVX()
{
	return vectorX;
}
int MonsterCollision::getVY()
{
	return vectorY;
}
int MonsterCollision::getST()
{
	return 0;
}

void MonsterCollision::SetLimitation(int x, int y, int width, int height)
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

void MonsterCollision::ImportTarget(int index)
{
	ActivateBrickIndex[count] = index;
	count++;
}

MonsterCollision::~MonsterCollision()
{

}