#include"Coordinate.h"

Coordinate::Coordinate(int xInTexture, int yInTexture, int xInWorld, int yInWorld)
{
	_xInTexture = xInTexture;
	_yInTexture = yInTexture;
	_xInWorld = xInWorld;
	_yInWorld = yInWorld;
}

Coordinate::~Coordinate()
{

}