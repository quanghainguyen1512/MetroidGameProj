#include"DoorManager.h"

DoorManager::DoorManager(CollisionManager* collisionManager, SpriteManager* spritemanager, GraphicsDevice* gDevice)
{
	COM = collisionManager;
	SM = spritemanager;
	_gDevice = gDevice;
}

DoorManager::~DoorManager()
{
	
}

void DoorManager::Initialize(string fileName)
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
		int target;
		int mode;
		string tag;
		std::istringstream iss(str);

		iss >> stt >> tag >> x >> y >> width >> height >> target >> mode;
		Import(stt, x, y, 0, 0, 0, mode);
	}
}

void DoorManager::Import(int stt, float x, float y, float rotation, float speed, float maxSpeed, int mode)
{
	Door* d = new Door(stt, x * 16, y * 16, rotation, 0, 0, COM, SM, _gDevice, "door", mode);
	d->Initialize(_gDevice->device);
	DList.push_back(d);
}

void DoorManager::update(int index)
{
	DList[index]->Update(0);
}

void DoorManager::draw(int index)
{
	DList[index]->Draw(0);
}