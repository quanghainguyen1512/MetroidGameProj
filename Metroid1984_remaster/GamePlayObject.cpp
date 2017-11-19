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

bool GameObject::Initialize(LPDIRECT3DDEVICE9 device, std::string file)
{
	name = file;
	return true;
}

void GameObject::Update(float gameTime)
{
}

void GameObject::Draw(float gameTime)
{
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
}