#include"BulletCollision.h"

BulletCollision::BulletCollision(int stt, float x, float y, float width, float height, string tag) :
Collision(stt, x, y, width, height, tag)
{
	ObjectIndex = stt;
}
bool BulletCollision::OnCollisionEnter(string &tag)
{
	Active = false;
	return true;
}
void BulletCollision::ImportTarget(int m)
{
	ObjectIndex = m;
}

BulletCollision::~BulletCollision()
{

}
