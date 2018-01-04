#include"Monster3.h"

Monster3::Monster3(int stt, float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spritemanager, GraphicsDevice* gDevice, string type, int mode) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager, spritemanager, gDevice)
{
	_type = type;
	Monster3CollisionIndex = stt;
	_stt = stt;
	velocity.x = 2;
	velocity.y = 0;
	vectorX = 1;
	vectorY = 0;
	bool Is_attack = false;
}

bool Monster3::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;
	if (!Move)
	{
		Move = new GameSprite(_spriteManager);
		if (!Move->initialize(device, _gDevice->getCharaterTex(), MONSTER3_INDEX, MONSTER3_COUNT))
			return false;
	}
	return true;
}

void Monster3::Update(float gameTime)
{
	vectorX = _collisionManager->getMonster(Monster3CollisionIndex)->getVX();
	vectorY = _collisionManager->getMonster(Monster3CollisionIndex)->getVY();

	position.x += vectorX*velocity.x;
	position.y += vectorY*velocity.y;
	_collisionManager->UpdateMonsterCol(Monster3CollisionIndex, position.x, position.y, velocity.x, velocity.y);

}

void Monster3::Draw(float gameTime)
{
	Move->Draw(gameTime, position);
}