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
	Brick* object = new Brick(stt, x * 16, y * 16, width * 16, height * 16, tag);
	BrickObject.push_back(object);

}
void CollisionManager::ImportPlayerCol(float x, float y, float width, float height)
{
	PlayerCol = new Collision(-1, x, y, width, height, "Player");
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

float CollisionManager::RemainYtime(float y0, float height, float VelocityY, string& Bricktag, string& MonsterTag)
{
	float min = 0;
	float Btime[20];
	float Mtime[20];
	BrickIndex = 0;
	MonsterIndex = 0;
	int brickIndex[20];
	int monsterIndex[20];

	for (int i = 0; i < CollisionList.size(); i++)
	{
		float result = BrickObject[CollisionList[i]]->YCollisionTime(y0, height, PlayerCol, VelocityY);
		if (result != 0)
		{
			Btime[BrickIndex] = result;
			brickIndex[BrickIndex] = i;
			BrickIndex++;

		}
		BrickObject[CollisionList[i]]->reset();
	}
	for (int i = 0; i < MonsterList.size(); i++)
	{
		float result = MonsterObject[MonsterList[i]]->YCollisionTime(y0, height, PlayerCol, VelocityY);
		if (MonsterObject[MonsterList[i]]->OnCollisionEnter(MonsterTag) == true)
		{
			MonsterTag = MonsterObject[MonsterList[i]]->getTag();
		}
		
		/*if (result != 0)
		{
			Mtime[MonsterIndex] = result;
			monsterIndex[MonsterIndex] = i;
			MonsterIndex++;

		}*/
	}
	if (BrickIndex > 0)
	{
		min = Btime[0];
		Bricktag = BrickObject[brickIndex[0]]->getTag();
	}
	for (int i = 0; i < BrickIndex; i++)
	{
		if (Btime[i] < min)
		{
			min = Btime[i];
			Bricktag = BrickObject[brickIndex[i]]->getTag();
		}
	}
	/*for (int i = 0; i < MonsterIndex; i++)
	{
		if (Mtime[i] < min)
		{
			min = Mtime[i];
			tag = MonsterObject[monsterIndex[i]]->getTag();
		}
	}*/
	if (min < 0)
		return 0;
	else
		return min;
}

float CollisionManager::RemainXtime(float x0, float width, float VelocityX, string& Bricktag, string& MonsterTag)
{
	float min = 0;
	float Btime[20];
	float Mtime[20];
	BrickIndex = 0;
	MonsterIndex = 0;
	int brickIndex[20];
	int monsterIndex[20];

	for (int i = 0; i < CollisionList.size(); i++)
	{
		float result = BrickObject[CollisionList[i]]->XCollisionTime(x0, width, PlayerCol, VelocityX);
		if (result != 0)
		{
			Btime[BrickIndex] = result;
			brickIndex[BrickIndex] = i;
			BrickIndex++;
		}
	}
	for (int i = 0; i < MonsterList.size(); i++)
	{
		float result = MonsterObject[MonsterList[i]]->XCollisionTime(x0, width, PlayerCol, VelocityX);
		if (MonsterObject[MonsterList[i]]->OnCollisionEnter(MonsterTag) == true)
		{
			MonsterTag = MonsterObject[MonsterList[i]]->getTag();
		}
		
		/*if (result != 0)
		{
			Mtime[MonsterIndex] = result;
			monsterIndex[MonsterIndex] = i;
			MonsterIndex++;
		}*/
	}
	if (BrickIndex > 0)
	{
		min = Btime[0];
		Bricktag = BrickObject[brickIndex[0]]->getTag();
	}

	for (int i = 0; i < BrickIndex; i++)
	{
		if (Btime[i] < min)
		{
			min = Btime[i];
			Bricktag = BrickObject[brickIndex[i]]->getTag();
		}
	}
	/*for (int i = 0; i < MonsterIndex; i++)
	{
		if (Mtime[i] < min)
		{
			min = Mtime[i];
			tag = MonsterObject[monsterIndex[i]]->getTag();
		}
	}*/
	if (min < 0)
		return 0;
	else
		return min;

}
void CollisionManager::ReadBrickData(string fileName)
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
	int startY = y / 16;
	int width16Pixel = _width / 16;
	int height16Pixel = _height / 16;

	int x16Pixel = (startX - 8);
	int y16Pixel = (startY - 8);

	vector<int> temp;

	_quadTree->Load2(temp, x16Pixel, y16Pixel, 16, 15);
	refresh(temp, x16Pixel * 16, y16Pixel * 16, 256, 240);
	MonsterAndBrick();
}

void CollisionManager::refresh(vector<int> v, int camx, int camy, int camwidth, int camheight)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (camy <= BrickObject[v[i]]->getY() && BrickObject[v[i]]->getY() < camy + camheight)
		{
			if (!(BrickObject[v[i]]->getX() + BrickObject[v[i]]->getWidth() < camx ||
				BrickObject[v[i]]->getX() > camx + camwidth))
			{
				if (BrickObject[v[i]]->Active == true)
				{
					CollisionList.push_back(v[i]);
					for (int e = 0; e < BrickObject[v[i]]->getCount(); e++)
					{
						if (MonsterObject[BrickObject[v[i]]->getMonster(e)]->Active == true)
							MonsterList.push_back(BrickObject[v[i]]->getMonster(e));
					}
				}
			}
		}
		if (camx <= BrickObject[v[i]]->getX() && BrickObject[v[i]]->getX() < camx + camwidth)
		{
			if (!(BrickObject[v[i]]->getY() + BrickObject[v[i]]->getHeight() < camy ||
				BrickObject[v[i]]->getY() > camy + camheight))
			{
				if (BrickObject[v[i]]->Active == true)
				{
					CollisionList.push_back(v[i]);
					for (int e = 0; e < BrickObject[v[i]]->getCount(); e++)
					{
						if (MonsterObject[BrickObject[v[i]]->getMonster(e)]->Active == true)
							MonsterList.push_back(BrickObject[v[i]]->getMonster(e));
					}
				}
			}
		}
	}
}

void CollisionManager::ImportQuadTree(QuadTree* Q)
{
	_quadTree = Q;
}
void CollisionManager::resetList()
{
	CollisionList.clear();
	MonsterList.clear();
}
Monster1Collision* CollisionManager::getMonster(int index)
{
	return MonsterObject[index];
}
void CollisionManager::ReadMonsterData(string fileName)
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
		int mode;
		std::istringstream iss(str);

		iss >> stt >> x >> y >> width >> height >> tag >> mode;
		ImportMonsterCollision(stt, x, y, width, height, tag, mode);
	}
}
void CollisionManager::ImportMonsterCollision(int stt, float x, float y, float width, float height, string tag, int mode)
{
	Monster1Collision* M = new Monster1Collision(stt, x * 16, y * 16, width * 16, height * 16, tag, mode);
	MonsterObject.push_back(M);
}
void CollisionManager::UpdateMonsterCol(int stt, float x, float y, float velocityX, float velocityY)
{
	MonsterObject[stt]->Update(x, y, 16, 16, velocityX, velocityY);
}

void CollisionManager::MonsterAndBrick()
{
	for (int i = 0; i < MonsterList.size(); i++)
	{
		if (MonsterObject[MonsterList[i]]->Active==true)
		{
			if (MonsterObject[MonsterList[i]]->getTag() == "monster1")
			{
				int e = 0;
				{
					int x = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e]]->getX();
					int y = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e]]->getY();
					int width = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e]]->getWidth();
					int height = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e]]->getHeight();

					MonsterObject[MonsterList[i]]->Climb(x, y, width, height);
				}
			}
			else if (MonsterObject[MonsterList[i]]->getTag() == "monster2")
			{
				int e = MonsterObject[MonsterList[i]]->count;
				int x = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getX();
				int y = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getY();
				int width = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getWidth();
				int height = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getHeight();

				MonsterObject[MonsterList[i]]->Fall(x, y, width, height, PlayerCol->getX(), PlayerCol->getY());
			}
			else if (MonsterObject[MonsterList[i]]->getTag() == "monster3")
			{
				int e = 1;
				int x = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getX();
				int y = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getY();
				int width = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getWidth();
				int height = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getHeight();

				MonsterObject[MonsterList[i]]->LeftRight(x, y, width, height);
			}
			else if (MonsterObject[MonsterList[i]]->getTag() == "monster4")
			{
				int e = MonsterObject[MonsterList[i]]->count;
				int x = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getX();
				int y = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getY();
				int width = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getWidth();
				int height = BrickObject[MonsterObject[MonsterList[i]]->ActivateBrickIndex[e - 1]]->getHeight();

				MonsterObject[MonsterList[i]]->Infinity(x, y, width, height,PlayerCol->getX(),PlayerCol->getY());
			}
		}
	}
}

void CollisionManager::ReadRelation(string fileName)
{
	ifstream file_txt(fileName);
	string str;
	string fileContent;
	while (getline(file_txt, str))
	{
		int monsterIndex;
		int brickIndex;
		std::istringstream iss(str);
		iss >> monsterIndex >> brickIndex;
		
		MonsterObject[monsterIndex]->ImportTarget(brickIndex);
		BrickObject[brickIndex]->ImportTarget(monsterIndex);
		if (MonsterObject[monsterIndex]->getTag() == "monster3")
		{
			int x = BrickObject[brickIndex]->getX();
			int y = BrickObject[brickIndex]->getY();
			int width = BrickObject[brickIndex]->getWidth();
			int height = BrickObject[brickIndex]->getHeight();

			MonsterObject[monsterIndex]->SetLimitation(x, y, width, height);
		}
	}
}