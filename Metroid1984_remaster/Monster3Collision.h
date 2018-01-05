#ifndef MONSTER3COLLISION_H
#define MONSTER3COLLISION_H

#include"MonsterCollision.h"

class  Monster3Collision :public MonsterCollision
{
public:
	Monster3Collision(
		int stt,
		float x,
		float y,
		float width,
		float height,
		string tag,
		int mode);
	~Monster3Collision();

	bool OnCollisionEnter(string &tag);
	void Orbit(int x, int y, int width, int height, int TargerX, int TargetY);
	int getST();

	void LeftRight(int x, int y, int width, int height);

	void SetLimitation(int x, int y, int width, int height);

private:
};

#endif