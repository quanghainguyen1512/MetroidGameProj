#ifndef COLLISION_H
#define COLLISION_H

#include<string>
#include <algorithm> 

using namespace std;

class Collision
{
public:
	Collision(int stt,float x, float y, float width, float height, string tag);
	~Collision();

	void Update(float x, float y, float width, float height, float velocityx, float velocityy);
	float SweptAABB(Collision* P, float &normalx, float &normaly);
	int SizeBySize(Collision* P);

	float YCollisionTime(float y0, float height, Collision* P, float VelocityY);
	float YCollisionTime(float y0, float yn, float Velocity, float height);

	float XCollisionTime(float x0, float width, Collision* P, float VelocityX);
	float XCollisionTime(float x0, float xn, float VelocitX, float width);

	string getTag();
protected:
	float _x;
	float _y;
	float _width;
	float _height;
	float _velocityX;
	float _velocityY;
	int _stt;
	string _tag;

};

#endif