#ifndef MONSTER3_H
#define MONSTER3_H

#include"GamePlayObject.h"
#include"DataSet.h"

class Monster3:public GameObject
{
public:
	 Monster3(
		 int stt,
		 float x,
		 float y,
		 float rotation,
		 float speed,
		 float maxSpeed,
		 CollisionManager* collisionManager,
		 SpriteManager* spritemanager,
		 GraphicsDevice* gDevice,
		 string type,
		 int mode);
	~ Monster3();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);
	void setVector(int vectorx, int vectory);

private:
	int Monster3CollisionIndex;
	string _type;
	int _stt;

	GameSprite* Move;
	GameSprite* Explosion;

	int vectorX;
	int vectorY;
	int spriteState;
	int spriteCount = 0;
	bool Destroy = false;
};

#endif