#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#define _USER_MATH_DEFINES
#include<cmath>
#include<math.h>
#include<string>
#include"GameSprite.h"

enum class ObjectStatus{ Active, Dying, Dead };

const float pi = 3.14159265359;

class GameObject
{
public:
	GameObject(float x, float y, float rotation, float speed, float maxSpeed);
	~GameObject();

	virtual bool Initialize(LPDIRECT3DDEVICE9 device);
	virtual void Update(float gameTime);
	virtual void Draw(float gameTime);

	ObjectStatus GetStatus() const;

	void SetSpeed(float speed);

protected:

	//physics data
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	float _rotation;
	float _speed;
	ObjectStatus status;
private:
	float _MaxSpeed;

	GameSprite* _Gs;

};

#endif