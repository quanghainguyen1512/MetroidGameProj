#ifndef MONSTER1COLLISION_H
#define MONSTER1COLLISION_H

#include"MonsterCollision.h"

class  Monster1Collision :public MonsterCollision
{
public:
	Monster1Collision(
		int stt, 
		float x, 
		float y, 
		float width, 
		float height, 
		string tag, 
		int mode);
	~Monster1Collision();

	bool OnCollisionEnter(string &tag);
	void Orbit(int x, int y, int width, int height, int TargerX, int TargetY);
	int getST();
	
	void Climb(int x, int y, int width, int height);

private:

};

#endif