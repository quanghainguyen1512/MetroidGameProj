#ifndef MONSTER2COLLISION_H
#define MONSTER2COLLISION_H

#include"MonsterCollision.h"

class  Monster2Collision :public MonsterCollision
{
public:
	Monster2Collision(
		int stt,
		float x,
		float y,
		float width,
		float height,
		string tag,
		int mode);
	~Monster2Collision();

	bool OnCollisionEnter(string &tag);
	void Orbit(int x, int y, int width, int height, int TargerX, int TargetY);
	int getST();

	void Fall(int x, int y, int width, int height, int targetX, int targetY);
	

private:
	
};

#endif