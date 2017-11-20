#include"GamePlayObject.h"

GameObject::GameObject(float x, float y, float rotation, float speed, float maxSpeed)
{
	float twopi = pi * 2;
	position.x = x;
	position.y = y;
	position.z = 0;

	if (rotation > twopi)
		rotation = twopi;
	if (rotation < 0)
		rotation = 0;

	if (speed > maxSpeed)
		speed = maxSpeed;
	if (speed < 0)
		speed = 0;

	_rotation = rotation;
	_speed = speed;

	velocity.x = cos(rotation)*speed;
	velocity.y = sin(rotation)*speed;
	velocity.z = 0;

	_MaxSpeed = maxSpeed;
}

bool GameObject::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;
	_Gs = new GameSprite();
	if (!_Gs->initialize(device,"Metroid_sprite_motion_2.png", 0, 0, 25, 38, 3))
	{
		return false;
	}

	return true;
}

void GameObject::Update(float gameTime)
{
	if (status == ObjectStatus::Active)
		_Gs->Update(gameTime);
}

void GameObject::Draw(float gameTime)
{
	if (_Gs)
		_Gs->Draw(gameTime, position);
}

ObjectStatus GameObject::GetStatus() const
{
	return status;
}

void GameObject::SetSpeed(float speed)
{
	if (speed >= 0 && speed <= _MaxSpeed)
	{
		_speed = speed;
		velocity.x = cos(_rotation)*speed;
		velocity.y = sin(_rotation)*speed;
		velocity.z = 0;
	}
}
GameObject::~GameObject()
{
	if (_Gs)
	{
		delete _Gs;
		_Gs = nullptr;
	}
}