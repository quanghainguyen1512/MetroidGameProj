#ifndef MONSTER4COLLISION_H
#define MONSTER4COLLISION_H

#include"MonsterCollision.h"

class  Monster4Collision :public MonsterCollision
{
public:
	Monster4Collision(
		int stt,
		float x,
		float y,
		float width,
		float height,
		string tag,
		int mode);
	~Monster4Collision();

	bool OnCollisionEnter(string &tag);
	void Orbit(int x, int y, int width, int height, int TargerX, int TargetY);
	int getST();

	void Infinity(int x, int y, int width, int height, int targetX, int targetY);

private:
};

#endif