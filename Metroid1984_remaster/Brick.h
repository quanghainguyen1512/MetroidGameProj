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
	void OnCollisionEnter(string &tag);

	void ImportTarget(int M);
	int getMonster(int index);
	int getCount();

protected:
	bool Destroyable;
	int monster[5];
	int count;

};

#endif