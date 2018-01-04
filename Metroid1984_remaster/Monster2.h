#ifndef MONSTER2_H
#define MONSTER2_H

#include"GamePlayObject.h"
#include"DataSet.h"

class Monster2:public GameObject
{
public:
	 Monster2(
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
	~ Monster2();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);
	void setVector(int vectorx, int vectory);

private:
	int Monster2CollisionIndex;
	string _type;
	int _stt;

	GameSprite* Spin;

	int vectorX;
	int vectorY;
	int StaticTime;
	int timecount;
	bool Is_attack;
};

#endif