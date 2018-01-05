#ifndef BULLETCOLLISION_H
#define BULLETCOLLISION_H

#include"Collision.h"

class  BulletCollision:public Collision
{
public:
	BulletCollision(
		int stt,
		float x,
		float y,
		float width,
		float height,
		string tag);
	~ BulletCollision();

	bool OnCollisionEnter(string &tag);
	void ImportTarget(int m);

private:
	int ObjectIndex;

};

#endif