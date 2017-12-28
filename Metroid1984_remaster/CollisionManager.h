#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include"Collision.h" 
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include"QuadTree.h"

using namespace std;

class CollisionManager
{
public:
	CollisionManager(int width, int height);
	~CollisionManager();
	
	void ReadData(string fileName);
	void ImportQuadTree(QuadTree* Q);
	void ImportCollision(int stt,float x, float y, float width, float height, string tag);
	void ImportPlayerCol(float x, float y, float width, float height);
	void UpdatePlayerCol(float x, float y, float width, float height, float velocityx, float velocityy);
	void resetList();

	void SetLimitation(int x, int y);

	int OnCollisionEnter();
	bool OnCollisionExit();
	float CheckCollision(float& normalx, float& normaly);
	int CheckSideBySide();

	float RemainYtime(float y0, float height, float VelocityY, string& tag);
	float RemainXtime(float x0, float width, float VelocityX, string& tag);

	int FixX();
	int FixY();

protected:
	Collision* PlayerCol;
	vector<Collision*> BrickObject;
	vector<int> CollisionList;
	QuadTree* _quadTree;

	int BrickIndex;

	int PlayerXAfter;
	int PlayerYAfter;

	float _normalx;
	float _normaly;

	int _width;
	int _height;

};

#endif