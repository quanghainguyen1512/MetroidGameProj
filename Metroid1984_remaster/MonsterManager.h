#ifndef MONSTERMANAGER_H
#define MONSTERMANAGER_H

#include"Monster1.h"
#include"Monster2.h"
#include"Monster3.h"
#include"Monster4.h"

class MonsterManager
{
public:
	MonsterManager(
		CollisionManager* collisionManager, 
		SpriteManager* spritemanager, 
		GraphicsDevice* gDevice);
	~MonsterManager();

	void Initialize(string fileName);
	void Import(int stt, float x, float y, float rotation, float speed, float maxSpeed, string tag, int mode);
	void update(int index);
	void draw(int index);
	void drawAll();
private:
	vector<GameObject*> MList;
	CollisionManager* COM;
	SpriteManager* SM;
	GraphicsDevice* _gDevice;
};


#endif