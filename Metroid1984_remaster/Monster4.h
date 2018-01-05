#ifndef MONSTER4_H
#define MONSTER4_H

#include"GamePlayObject.h"
#include"DataSet.h"

class Monster4 :public GameObject
{
public:
	Monster4(
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
	~Monster4();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);
	void setVector(int vectorx, int vectory);

private:
	int Monster4CollisionIndex;
	string _type;
	int _stt;

	GameSprite* Move;

	int vectorX;
	int vectorY;
};

#endif