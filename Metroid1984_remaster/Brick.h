#ifndef BRICK_H
#define BRICK_H

#include"Collision.h";

class Brick:public Collision
{
public:
	Brick(
		int stt, 
		float x, 
		float y, 
		float width, 
		float height, 
		string tag);
	~Brick();
	bool OnCollisionEnter(string &tag);

	void ImportTarget(int M);
	int getMonster(int index);
	int getCount();
	void ImportDoor(int D);
	int getDoorIndex();

protected:
	bool Destroyable;
	int monster[20];
	int count;

	int doorIndex;

};

#endif