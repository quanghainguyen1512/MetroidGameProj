#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include"Brick.h" 
#include"Monster1Collision.h"
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
	
	void ReadBrickData(string fileName);
	void ReadMonsterData(string fileName);
	void ReadRelation(string fileName);

	void ImportQuadTree(QuadTree* Q);
	void ImportCollision(int stt,float x, float y, float width, float height, string tag);
	void ImportMonsterCollision(int stt, float x, float y, float width, float hegith, string tag, int mode);
	void ImportPlayerCol(float x, float y, float width, float height);
	
	void UpdatePlayerCol(float x, float y, float width, float height, float velocityx, float velocityy);
	void UpdateMonsterCol(int stt, float x, float y, float velocityX, float velocityY);
	void resetList();

	void SetLimitation(int x, int y);

	int OnCollisionEnter();
	bool OnCollisionExit();
	float CheckCollision(float& normalx, float& normaly);

	void refresh(vector<int> v, int camx, int camy, int camwidth, int camheight);

	float RemainYtime(float y0, float height, float VelocityY, string& tag);
	float RemainXtime(float x0, float width, float VelocityX, string& tag);

	void MonsterAndBrick();

	int FixX();
	int FixY();

	Monster1Collision* getMonster(int index);
	
	vector<int> MonsterList;
	vector<int> CollisionList;

protected:
	Collision* PlayerCol;
	vector<Brick*> BrickObject;
	vector<Monster1Collision*> MonsterObject;
	
	QuadTree* _quadTree;

	int BrickIndex;
	int MonsterIndex;

	int PlayerXAfter;
	int PlayerYAfter;

	float _normalx;
	float _normaly;

	int _width;
	int _height;

};

#endif