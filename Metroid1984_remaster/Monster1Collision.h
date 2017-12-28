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

	void OnCollisionEnter(string &tag);
	void ImportTarget(int index);
	void Climb(int x, int y, int width, int height);
	int GetActiveArea(int index);

	int getVX();
	int getVY();
	int getST();
	
	int ActivateBrickIndex[5];
	int count;

private:
	int TargetIndex;
	bool leftRight = false;

	int vectorX;
	int vectorY;
	int spriteState;
};

#endif