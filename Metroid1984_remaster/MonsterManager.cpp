#include"MonsterManager.h"

MonsterManager::MonsterManager(CollisionManager* collisionManager, SpriteManager* spritemanager, GraphicsDevice* gDevice)
{
	COM = collisionManager;
	SM = spritemanager;
	_gDevice = gDevice;
}
MonsterManager::~MonsterManager()
{

}
 
void MonsterManager::Initialize(string fileName)
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
		Import(stt, x, y, 0, 1, 1, tag, mode);
	}
}

void MonsterManager::Import(int stt, float x, float y, float rotation, float speed, float maxSpeed, string tag, int mode)
{
	if (tag == "monster1")
	{
		GameObject* m = new Monster1(stt, x * 16, y * 16, rotation, speed, maxSpeed, COM, SM, _gDevice, tag, mode);
		m->Initialize(_gDevice->device);
		MList.push_back(m);
	}
	else if (tag == "monster2")
	{
		GameObject* m = new Monster2(stt, x * 16, y * 16, rotation, speed, maxSpeed, COM, SM, _gDevice, tag, mode);
		m->Initialize(_gDevice->device);
		MList.push_back(m);
	}
	else if (tag == "monster3")
	{
		GameObject* m = new Monster3(stt, x * 16, y * 16, rotation, speed, maxSpeed, COM, SM, _gDevice, tag, mode);
		m->Initialize(_gDevice->device);
		MList.push_back(m);
	}
	else if (tag == "monster4")
	{
		GameObject* m = new Monster4(stt, x * 16, y * 16, rotation, speed, maxSpeed, COM, SM, _gDevice, tag, mode);
		m->Initialize(_gDevice->device);
		MList.push_back(m);
	}
}

void MonsterManager::update(int index)
{
	MList[index]->Update(0);
}

void MonsterManager::draw(int index)
{
	MList[index]->Draw(0);
}

void MonsterManager::drawAll()
{
	for (int i = 0; i < MList.size(); i++)
	{
		MList[i]->Draw(0);
	}
}