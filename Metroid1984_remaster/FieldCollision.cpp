#include"FieldCollision.h"

FieldCollision::FieldCollision(int stt, float x, float y, float width, float height, string tag, int mode) :
Collision(stt, x, y, width, height, tag)
{
	_mode = mode;
}

bool FieldCollision::OnCollisionEnter(string &tag)
{
	return true;
}

int FieldCollision::getmode()
{
	return _mode;
}
void FieldCollision::ImportTarget(int m)
{

}

FieldCollision::~FieldCollision()
{

}