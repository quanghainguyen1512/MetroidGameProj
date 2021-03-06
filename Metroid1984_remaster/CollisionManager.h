#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include"Brick.h" 
#include"Monster1Collision.h"
#include"Monster2Collision.h"
#include"Monster3Collision.h"
#include"Monster4Collision.h"
#include"BulletCollision.h"
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
	void ImportBulletCollision(int stt, float x, float y, float width, float height);
	void ImportPlayerCol(float x, float y, float width, float height);
	
	void UpdatePlayerCol(float x, float y, float width, float height, float velocityx, float velocityy);
	void UpdateMonsterCol(int stt, float x, float y, float velocityX, float velocityY);
	void UpdateBulletCol(int stt, float x, float y, float velocityX, float velocityY,bool active);
	void resetList();

	void SetLimitation(int x, int y);

	int OnCollisionEnter();
	bool OnCollisionExit();
	float CheckCollision(float& normalx, float& normaly);

	void refresh(vector<int> v, int camx, int camy, int camwidth, int camheight);

	float RemainYtime(float y0, float height, float VelocityY, string& Bricktag, string& MonsterTag);
	float RemainXtime(float x0, float width, float VelocityX, string& Bricktag, string& MonsterTag);

	void MonsterAndBrick();
	void BulletProcess();

	int FixX();
	int FixY();

	MonsterCollision* getMonster(int index);
	bool getBulletActive(int i);
	
	vector<int> MonsterList;
	vector<int> CollisionList;

protected:
	Collision* PlayerCol;
	vector<Brick*> BrickObject;
	vector<MonsterCollision*> MonsterObject;
	vector<BulletCollision*>BulletList;
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