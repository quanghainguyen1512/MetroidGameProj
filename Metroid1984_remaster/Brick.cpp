#include"Brick.h"

Brick::Brick(int stt, float x, float y, float width, float height, string tag) :
Collision(stt, x, y, width, height, tag)
{
	_velocityX = 0;
	_velocityY = 0;
	if (tag == "brick2")
	{
		Destroyable = true;
	}
	count = 0;
	doorIndex = -1;
}

bool Brick::OnCollisionEnter(string &tag)
{
	if (Destroyable == true)
	{
		if (tag == "Bullet")
		{
			Active = false;
			return true;
		}
	}
	return false;
}

void Brick::ImportTarget(int M)
{
	monster[count] = M;
	count++;
}

int Brick::getMonster(int index)
{
	return monster[index];
}
int Brick::getCount()
{
	return count;
}

void Brick::ImportDoor(int D)
{
	doorIndex = D;
}

int Brick::getDoorIndex()
{
	return doorIndex;
}

Brick::~Brick()
{

}