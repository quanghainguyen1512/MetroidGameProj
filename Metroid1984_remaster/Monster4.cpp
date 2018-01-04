#include"Monster4.h"

Monster4::Monster4(int stt, float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spritemanager, GraphicsDevice* gDevice, string type, int mode) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager, spritemanager, gDevice)
{
	_type = type;
	Monster4CollisionIndex = stt;
	_stt = stt;
	velocity.x = 1;
	velocity.y = 3;
	vectorX = 0;
	vectorY = 0;
	bool Is_attack = false;
}

bool Monster4::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;

	if (!Move)
	{
		Move = new GameSprite(_spriteManager);
		if (!Move->initialize(device, _gDevice->getCharaterTex(), MONSTER4_INDEX, MONSTER4_COUNT))
			return false;
	}

	return false;
}

void Monster4::Update(float gameTime)
{
	vectorX = _collisionManager->getMonster(Monster4CollisionIndex)->getVX();
	vectorY = _collisionManager->getMonster(Monster4CollisionIndex)->getVY();

	position.x += vectorX*velocity.x;
	position.y += vectorY*velocity.y;
	_collisionManager->UpdateMonsterCol(Monster4CollisionIndex, position.x, position.y, velocity.x, velocity.y);

}

void Monster4::Draw(float gameTime)
{
	Move->Draw(gameTime, position);
}