#include"Bullet.h"

Bullet::Bullet(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spritemanager, GraphicsDevice* gDevice):
GameObject(x,y,rotation,speed,maxSpeed,collisionManager,spritemanager,gDevice)
{
	velocity.x = 0.25;
	velocity.y = 0.25;
	startX = x;
	startY = y;
	activeTime = 0;
	vx0 = 0; vy0 = 0;
}
Bullet::~Bullet()
{

}

bool Bullet::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;

	if (!Shape)
	{
		Shape = new GameSprite(_spriteManager);
		if (!Shape->initialize(device, _gDevice->getCharaterTex(), BULLET_INDEX, BULLET_COUNT))
			return false;
	}
	return true;
}

void Bullet::Update(float gameTime)
{
	if (active == true)
	{
		position.x += vectorX*(velocity.x + vx0)*gameTime;
		position.y += vectorY*(velocity.y + vy0)*gameTime;
		//_collisionManager->UpdateMonsterCol();
		if (activeTime == 7)
		{
			Reset();
		}
		activeTime++;
	}
}

void Bullet::Draw(float gameTime)
{
	Shape->Draw(gameTime, position);
}
void Bullet::SetVector(int vectorx, int vectory, float Vx0, float Vy0)
{
	vectorX = vectorx;
	vectorY = vectory;
	vx0 = Vx0;
	vy0 = Vy0;
}

void Bullet::UpdatePosition(float x, float y)
{
	position.x = x;
	position.y = y;

	startX = x;
	startY = y;
}

void Bullet::Reset()
{
	position.x = startX;
	position.y = startY;
	activeTime = 0;
	active = false;
	vx0 = 0;
	vy0 = 0;
}

