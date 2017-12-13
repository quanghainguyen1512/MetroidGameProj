#include"CollisionManager.h"

CollisionManager::CollisionManager()
{
	ImportCollision(37, 207, 112, 16, "brick");
}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::ImportCollision(float x, float y, float width, float height,string tag)
{
	Collision* object= new Collision(x * 16, y * 16, width, height, tag);
	BrickObject.push_back(object);
	
}
void CollisionManager::ImportPlayerCol(float x, float y, float width, float height)
{
	PlayerCol = new Collision(x, y, width, height, "Player");
}
void CollisionManager::UpdatePlayerCol(float x, float y, float width, float height, float velocityx, float velocityy)
{
	PlayerCol->Update(x, y, width, height, velocityx, velocityy);
}
int CollisionManager::OnCollisionEnter()
{
	return 1;
}
bool CollisionManager::OnCollisionExit()
{
	return false;
}
int CollisionManager::FixX()
{
	return PlayerXAfter;
}
int CollisionManager::FixY()
{
	return PlayerYAfter;
}

float CollisionManager::CheckCollision(float& normalx, float& normaly)
{
	int index = 0;
	float min = BrickObject[0]->SweptAABB(PlayerCol, _normalx, _normaly);
	for (int i = 0; i < BrickObject.size(); i++)
	{
		float result = BrickObject[i]->SweptAABB(PlayerCol, _normalx, _normaly);
		if (result < min&& result != 1)
		{
			result = min;
		}
	}
	normalx = _normalx;
	normaly = _normaly;
	return min;
}

float CollisionManager::RemainYtime(float y0, float VelocityY)
{
	float min = 0;
	float time[10];
	BrickIndex = 0;
	for (int i = 0; i < BrickObject.size(); i++)
	{
		float result = BrickObject[i]->YCollisionTime(y0, PlayerCol, VelocityY);
		if (result != 0)
		{
			time[BrickIndex] = result;
			BrickIndex++;
		}
	}

	min = time[0];
	for (int i = 0; i < BrickIndex; i++)
	{
		if (time[i] < min)
		{
			min = time[i];
		}
	}
	if (min < 0)
		return 0;
	else
		return min;
}

float CollisionManager::RemainXtime(float x0, float VelocityX)
{
	float min = 0;
	float time[10];
	BrickIndex = 0;
	for (int i = 0; i < BrickObject.size(); i++)
	{
		float result = BrickObject[i]->XCollisionTime(x0, PlayerCol, VelocityX);
		if (result != 0)
		{
			time[BrickIndex] = result;
			BrickIndex++;
		}
	}
	min = time[0];
	for (int i = 0; i < BrickIndex; i++)
	{
		if (time[i] < min)
		{
			min = time[i];
		}
	}
	if (min < 0)
		return 0;
	else
		return min;

}

int CollisionManager::CheckSideBySide()
{
	for ( int i = 0; i < BrickObject.size(); i++)
	{
		int result = BrickObject[i]->SizeBySize(PlayerCol);
		if (result != 0)
			return result;
	}
	return 0;
}