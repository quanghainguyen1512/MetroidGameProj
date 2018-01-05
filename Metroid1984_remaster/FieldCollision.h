#ifndef FIELDCOLLISION_H
#define FIELDCOLLISION_H

#include"Collision.h"

class FieldCollision:public Collision
{
public:
	FieldCollision(
		int stt,
		float x,
		float y,
		float width,
		float height,
		string tag,
		int mode);
	~ FieldCollision();

	bool OnCollisionEnter(string &tag);
	void ImportTarget(int M);
	
	int getmode();

private:
	int _mode;
};
#endif