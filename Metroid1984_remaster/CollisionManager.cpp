#include"CollisionManager.h"

using namespace std;

CollisionManager::CollisionManager(int width, int height)
{
	_width = width;
	_height = height;
}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::ImportCollision(int stt, float x, float y, float width, float height, string tag)
{
	Collision* object = new Collision(stt, x * 16, y * 16, width * 16, height * 16, tag);
	BrickObject.push_back(object);

}
void CollisionManager::ImportPlayerCol(float x, float y, float width, float height)
{
	PlayerCol = new Collision(-1, x, y, width, height, "Player");
}
void CollisionManager::UpdatePlayerCol(float x, float y, float width, float height, float velocityx, float velocityy)
{
	PlayerCol->Update(x, y, width, height, velocityx, velocityy);
	//SetLimitation(x, y);
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

float CollisionManager::RemainYtime(float y0, float height, float VelocityY, string& tag)
{
	float min = 0;
	float time[10];
	BrickIndex = 0;
	int index[10];
	for (int i = 0; i < CollisionList.size(); i++)
	{
		float result = BrickObject[CollisionList[i]]->YCollisionTime(y0, height, PlayerCol, VelocityY);
		tag = BrickObject[CollisionList[i]]->getTag();
		if (result != 0)
		{
			time[BrickIndex] = result;
			index[BrickIndex] = i;
			BrickIndex++;

		}
	}

	min = time[0];
	for (int i = 0; i < BrickIndex; i++)
	{
		if (time[i] < min)
		{
			min = time[i];
			tag = BrickObject[index[i]]->getTag();
		}
	}
	if (min < 0)
		return 0;
	else
		return min;
}

float CollisionManager::RemainXtime(float x0, float width, float VelocityX, string& tag)
{
	float min = 0;
	float time[10];
	BrickIndex = 0;
	int index[10];
	for (int i = 0; i < CollisionList.size(); i++)
	{
		float result = BrickObject[CollisionList[i]]->XCollisionTime(x0, width, PlayerCol, VelocityX);
		if (result != 0)
		{
			time[BrickIndex] = result;
			index[BrickIndex] = i;
			BrickIndex++;
		}
	}
	min = time[0];
	for (int i = 0; i < BrickIndex; i++)
	{
		if (time[i] < min)
		{
			min = time[i];
			tag = BrickObject[index[i]]->getTag();
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

void CollisionManager::ReadData(string fileName)
{
	ifstream file_txt(fileName);
	string str;
	string fileContent;
	while (getline(file_txt, str))
	{
		int stt;
		int x;
		int y;
		int width;
		int height;
		string tag;
		std::istringstream iss(str);

		iss >> stt >> tag >> x >> y >> width >> height;
		ImportCollision(stt, x, y, width, height, tag);
	}
}

void CollisionManager::SetLimitation(int x, int y)
{
	int startX = x / 16;
	int starty = y / 16;
	int width16Pixel = _width / 16;
	int height16Pixel = _height / 16;
	int x16Pixel = (x - _width / 2) / 16;
	int y16Pixel = (y - _height / 2) / 16;

	_quadTree->Load(CollisionList, x16Pixel, y16Pixel, width16Pixel, height16Pixel);

}

void CollisionManager::ImportQuadTree(QuadTree* Q)
{
	_quadTree = Q;
}
void CollisionManager::resetList()
{
	CollisionList.clear();
}