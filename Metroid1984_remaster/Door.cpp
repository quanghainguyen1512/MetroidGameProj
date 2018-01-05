#include"Door.h"

Door::Door(int stt,float x,float y,float rotation,float speed,float maxSpeed,CollisionManager* collisionManager,SpriteManager* spritemanager,GraphicsDevice* gDevice,string type,int mode):
GameObject(x,y,rotation,speed,maxSpeed,collisionManager,spritemanager,gDevice)
{
	_stt = stt;
	DoorCollisionIndex = stt;
	active = false;
	leftdestroy = false;
	rightdestroy = false;

	CamMode = mode;
}

bool Door::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;

	if (!LeftDoor)
	{
		LeftDoor = new GameSprite(_spriteManager);
		if (!LeftDoor->initialize(device, _gDevice->getCharaterTex(), LEFTDOOR_INDEX, DOOR_COUNT))
			return false;
	}

	if (!RightDoor)
	{
		RightDoor = new GameSprite(_spriteManager);
		if (!RightDoor->initialize(device, _gDevice->getCharaterTex(), RIGHTDOOR_INDEX, DOOR_COUNT))
			return false;
	}

	return true;
}

void Door::Update(float gameTime)
{
	switch (_collisionManager->getDoor(DoorCollisionIndex)->getST())
	{
	case 1:
	{
		leftdestroy = true;
		break;
	}
	case 2:
	{
		rightdestroy = true;
		break;
	}
	case 0:
	{
		active = true;
		break;
	}
	case 3:
	{
		leftdestroy = true;
		rightdestroy = true;
	}

	default:
		break;
	}
}

void Door::Draw(float gameTime)
{
	if (active == true)
	{
		if (rightdestroy == false && leftdestroy == false)
		{
			LeftDoor->Draw(gameTime, D3DXVECTOR3(position.x + 8, position.y, 0));
			RightDoor->Draw(gameTime, D3DXVECTOR3(position.x + 48, position.y, 0));
		}
		else
		{
			if (rightdestroy == true && leftdestroy != true)
				LeftDoor->Draw(gameTime, D3DXVECTOR3(position.x + 8, position.y, 0));
			if (leftdestroy == true && rightdestroy != true)
				RightDoor->Draw(gameTime, D3DXVECTOR3(position.x + 48, position.y, 0));
		}
	}
}