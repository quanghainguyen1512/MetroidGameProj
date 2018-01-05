#ifndef MONSTERCOLLISION_H
#define MONSTERCOLLISION_H

#include"Collision.h"

class  MonsterCollision :public Collision
{
public:

	 MonsterCollision(
		 int stt,
		 float x,
		 float y,
		 float width,
		 float height,
		 string tag,
		 int mode);
	~ MonsterCollision();

	virtual bool OnCollisionEnter(string &tag);
	void ImportTarget(int index);
	virtual void Orbit(int x, int y, int width, int height, int TargerX, int TargetY);

	int GetActiveArea(int index);

	int getVX();
	int getVY();
	virtual int getST();

	void SetLimitation(int x, int y, int width, int height);

	int ActivateBrickIndex[5];
	int count;

protected:
	int TargetIndex;
	bool leftRight = false;
	bool attack;

	int vectorX;
	int vectorY;
	int spriteState;
	int timeCount = 0;

	int maxX;
	int minX;

	int Destroy;
};

#endif