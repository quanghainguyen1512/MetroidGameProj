#ifndef DOORMANAGER_H
#define DOORMANAGER_H

#include"Door.h"

class DoorManager
{
public:
	DoorManager(
		CollisionManager* collisionManager,
		SpriteManager* spritemanager,
		GraphicsDevice* gDevice);
	~DoorManager();

	void Initialize(string fileName);
	void Import(int stt, float x, float y, float rotation, float speed, float maxSpeed, int mode);
	void update(int index);
	void draw(int index);

private:
	vector<Door*>DList;
	CollisionManager*COM;
	SpriteManager* SM;
	GraphicsDevice* _gDevice;

};

#endif