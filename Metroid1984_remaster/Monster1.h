#ifndef MONSTER1_H
#define MONSTER1_H

#include"GamePlayObject.h"

class Monster1 :public GameObject
{
public:
	Monster1(
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
	~Monster1();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);

	void setVector(int vectorx, int vectory);

private:
	int Monster1CollisionIndex;
	string _type;
	bool leftright;
	int _stt;

	GameSprite* Up;
	GameSprite* Down;
	GameSprite* Right;
	GameSprite* Left;

	bool left_right;

	int vectorX;
	int vectorY;
	int spriteState;
};

#endif
