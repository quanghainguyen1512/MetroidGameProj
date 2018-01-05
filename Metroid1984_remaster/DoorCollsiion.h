#ifndef DOORCOLLISION_H
#define DOORCOLLISION_H

#include"Collision.h"

class  DoorCollision :public Collision
{
public:
	DoorCollision(
		int stt,
		float x,
		float y,
		float width,
		float height,
		string tag,
		int mode);
	~ DoorCollision();

	void ImportTarget(int index);
	bool OnCollisionEnter(string &tag);
	int getST();

	bool getLeft();
	bool getRight();
	void setActive(bool a);
	int getMode();
	void reset();
	
	bool GetThrough;
private:
	int TargetIndex;
	bool LeftDestroy;
	bool RightDestroy;
	

	int brickIndex;
	int _mode;

};


#endif