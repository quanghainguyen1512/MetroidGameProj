#ifndef BULLET_H
#define BULLET_H

#include"GamePlayObject.h"
#include"DataSet.h"

class Bullet:public GameObject
{
public:
	Bullet(
		float x,
		float y,
		float rotation,
		float speed,
		float maxSpeed,
		CollisionManager* collisionManager,
		SpriteManager* spritemanager,
		GraphicsDevice* gDevice);
	~ Bullet();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);

	void SetVector(int vectorx, int vectory, float Vx0, float Vy0);
	void UpdatePosition(float x, float y);
	void Reset();

	bool active;

private:
	GameSprite* Shape;

	bool Is_initialzed = false;

	int limitationX;
	int limitationY;
	int vectorX;
	int vectorY;

	int vx0;
	int vy0;
	
	float startX;
	float startY;
	int activeTime;
};

#endif