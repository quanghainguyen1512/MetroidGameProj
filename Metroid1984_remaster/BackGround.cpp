#include"BackGround.h"

BackGround::BackGround(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spriteManager, GraphicsDevice* gDevice) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager, spriteManager, gDevice)
{

}

bool BackGround::Initialize(LPDIRECT3DDEVICE9 device)
{
	if (!image)
	{
		image = new GameSprite(_spriteManager);
		if (!image->initialize(device, _gDevice->getCharaterTex(),0, 1))
		{
			return false;
		}
	}

	is_initialize = true;

	return true;
}


void BackGround::Update(float gameTime){}

void BackGround::Draw(float gameTime)
{
	image->Draw(gameTime, position);
}

BackGround::~BackGround()
{
	if (image)
	{
		delete image;
		image = nullptr;
	}
}