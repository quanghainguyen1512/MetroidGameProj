#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include"Collision.h" 
#include<vector>


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void ImportCollision(float x, float y, float width, float height,string tag);
	void ImportPlayerCol(float x, float y, float width, float height);
	void UpdatePlayerCol(float x, float y, float width, float height,float velocityx, float velocityy);

	int OnCollisionEnter();
	bool OnCollisionExit();
	float CheckCollision(float& normalx, float& normaly);
	int CheckSideBySide();

	float RemainYtime(float y0, float VelocityY);
	float RemainXtime(float x0, float VelocityX);

	int FixX();
	int FixY();

protected:
	Collision* PlayerCol;
	vector<Collision*> BrickObject;

	int BrickIndex;

	int PlayerXAfter;
	int PlayerYAfter;

	float _normalx;
	float _normaly;

};

#endif