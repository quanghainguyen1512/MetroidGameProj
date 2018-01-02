#ifndef MONSTER1COLLISION_H
#define MONSTER1COLLISION_H

#include"Collision.h"

class  Monster1Collision :public Collision
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
	void ImportTarget(int index);
	void Orbit(int x, int y, int width, int height, int TargerX, int TargetY);
	
	void Climb(int x, int y, int width, int height);
	void Fall(int x, int y, int width, int height, int targetX, int targety);
	void LeftRight(int x, int y, int width, int height);
	void Infinity(int x, int y, int width, int height);
	void Follow(int x, int y, int width, int height);

	int GetActiveArea(int index);


	int getVX();
	int getVY();
	int getST();
	
	int ActivateBrickIndex[5];
	int count;

private:
	int TargetIndex;
	bool leftRight = false;
	bool attack;

	int vectorX;
	int vectorY;
	int spriteState;
	int timeCount = 0;
};

#endif