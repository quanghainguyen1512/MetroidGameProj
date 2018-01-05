#include"Map.h"

using namespace std;

Map::Map(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spriteManager, GraphicsDevice* gDevice) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager, spriteManager, gDevice)
{

}

bool Map::Initialize(LPDIRECT3DDEVICE9 device)
{
	halfofmap_left = new Field(16, 16, 0, 0, 0, NULL, "halfofmap_left2.txt", _spriteManager, _gDevice);
	if (halfofmap_left->Initialize(device) == false)
	{
		return false;
	}
	IsInitialize = true;
	return true;
}


void Map::Draw(float gameTime)
{
	halfofmap_left->Draw(gameTime);
}

void Map::setLimitation(int camX, int camY, int width, int height, int playerX, int playerY)
{
	halfofmap_left->setLimitation(camX, camY, width, height);
	_collisionManager->SetLimitation(playerX, playerY);
}

void Map::Update(float gameTime)
{

}

void Map::ImportCollisionManager(CollisionManager* c)
{
	_collisionManager = c;
}

Map::~Map()
{
	if (halfofmap_left)
	{
		delete halfofmap_left;
		halfofmap_left = nullptr;
	}
}