#include"Monster1.h"

Monster1::Monster1(int stt, float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spritemanager, GraphicsDevice* gDevice,string type, int mode) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager, spritemanager,gDevice)
{
	_type = type;
	Monster1CollisionIndex = stt;
	_stt = stt;
	leftright = mode;
	velocity.x = 1;
	velocity.y = 1;
	spriteState = 3;
	vectorX = 1;
	vectorY = 0;
}

bool Monster1::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;

	if (!Up)
	{
		Up = new GameSprite(_spriteManager);
		if (!Up->initialize(device, _gDevice->getCharaterTex(), MONSTER1_UP_INDEX, MONSTER1_COUNT))
			return false;
	}

	if (!Down)
	{
		Down = new GameSprite(_spriteManager);
		if (!Down->initialize(device, _gDevice->getCharaterTex(), MONSTER1_DOWN_INDEX, MONSTER1_COUNT))
			return false;
	}

	if (!Left)
	{
		Left = new GameSprite(_spriteManager);
		if (!Left->initialize(device, _gDevice->getCharaterTex(), MONSTER1_LEFT_INDEX, MONSTER1_COUNT))
			return false;
	}

	if (!Right)
	{
		Right = new GameSprite(_spriteManager);
		if (!Right->initialize(device, _gDevice->getCharaterTex(), MONSTER1_RIGHT_INDEX, MONSTER1_COUNT))
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

void Monster1::Update(float gameTime)
{
	vectorX = _collisionManager->getMonster(Monster1CollisionIndex)->getVX();
	vectorY = _collisionManager->getMonster(Monster1CollisionIndex)->getVY();
	if (Destroy == false)
		spriteState = _collisionManager->getMonster(Monster1CollisionIndex)->getST();

	position.x += vectorX*velocity.x;
	position.y += vectorY*velocity.y;
	_collisionManager->UpdateMonsterCol(Monster1CollisionIndex, position.x, position.y, velocity.x, velocity.y);

	if (spriteState == -1)
	{
		Destroy = true;
	}
	if (Destroy == true)
	{
		Explosion->Update(gameTime);
		spriteCount++;
	}
	if (spriteCount > 2)
	{
		_collisionManager->getMonster(Monster1CollisionIndex)->Active = false;
	}
}

void Monster1::Draw(float gameTime)
{
	switch (spriteState)
	{
	case -1:
	{
		Explosion->Draw(gameTime, position);
		break;
	}
	case 0:
	{
		Right->Draw(gameTime, position);	
		break;
	}
	case 1:
	{
		Down->Draw(gameTime, position);
		break;
	}
	case 2:
	{
		Left->Draw(gameTime, position);
		break;
	}
	case 3:
	{
		Up->Draw(gameTime, position);
		break;
	}

	default:
		break;
	}
}

void Monster1::setVector(int vectorx, int vectory)
{
	vectorX = vectorx;
	vectorY = vectory;
}


Monster1::~Monster1()
{

}
