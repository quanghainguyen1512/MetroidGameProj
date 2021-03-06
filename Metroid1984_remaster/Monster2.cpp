#include"Monster2.h"

Monster2::Monster2(int stt,	float x,float y,float rotation,float speed,	float maxSpeed,	CollisionManager* collisionManager,	SpriteManager* spritemanager,GraphicsDevice* gDevice,string type,int mode) :
	GameObject(x, y, rotation, speed, maxSpeed, collisionManager, spritemanager, gDevice)
{
	_type = type;
	Monster2CollisionIndex = stt;
	_stt = stt;
	
	velocity.x = 4;
	velocity.y = 4;

	vectorX = 0;
	vectorY = 0;

	StaticTime = 5;
	timecount = 0;
	bool Is_attack = false;
}

bool Monster2::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;

	if (!Spin)
	{
		Spin = new GameSprite(_spriteManager);
		if (!Spin->initialize(device, _gDevice->getCharaterTex(), MONSTER2_INDEX, MONSTER2_COUNT))
			return false;
	}
	if (!Explosion)
	{
		Explosion = new GameSprite(_spriteManager);
		if (!Explosion->initialize(device, _gDevice->getCharaterTex(), EXPLOSION_INDEX, EXPLOSION_COUNT))
			return false;
	}

	return true;
}

void Monster2::Update(float gameTime)
{
	vectorX = _collisionManager->getMonster(Monster2CollisionIndex)->getVX();
	vectorY = _collisionManager->getMonster(Monster2CollisionIndex)->getVY();
	Is_attack = _collisionManager->getMonster(Monster2CollisionIndex)->getST();
	if (Destroy == false)
		spriteState = _collisionManager->getMonster(Monster2CollisionIndex)->getST();

	position.x += vectorX*velocity.x;
	position.y += vectorY*velocity.y;
	_collisionManager->UpdateMonsterCol(Monster2CollisionIndex, position.x, position.y, velocity.x, velocity.y);

	timecount++;

	if (spriteState == -1)
	{
		Destroy = true;
	}
	else
	{
		if (Is_attack == false)
		{
			if (timecount % StaticTime == 0)
			{
				Spin->Update(gameTime);
			}
		}
		else
		{
			Spin->Update(gameTime);
		}
	}
	if (Destroy == true)
	{
		Explosion->Update(gameTime);
		spriteCount++;
	}
	if (spriteCount >= 2)
	{
		_collisionManager->getMonster(Monster2CollisionIndex)->Active = false;
	}
}

void Monster2::Draw(float gameTime)
{
	if (spriteState == -1)
	{
		Explosion->Draw(gameTime, position);
	}
	Spin->Draw(gameTime, position);
}