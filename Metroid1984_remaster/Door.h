#ifndef DOOR_H
#define DOOR_H

#include"GamePlayObject.h"
#include"DataSet.h"

class Door: public GameObject
{
public:
	Door(int stt,
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
	~Door();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);

private:
	int DoorCollisionIndex;
	bool active;
	bool leftdestroy;
	bool rightdestroy;
	int _stt;

	int CamMode;

	GameSprite* LeftDoor;
	GameSprite* RightDoor;

};

#endif