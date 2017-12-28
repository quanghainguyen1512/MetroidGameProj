#include"GamePlayObject.h"
#include"Coordinate.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Field :public GameObject
{
public:
	Field(float x, 
		  float y, 
		  float rotation, 
		  float speed, 
		  float maxSpeed, 
		  CollisionManager* collisionManager, 
		  std::string file, 
		  LPDIRECT3DTEXTURE9 SourceTex, 
		  SpriteManager* spriteManager);
	~Field();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);
	bool CreateTexture(LPDIRECT3DDEVICE9 device, std::string file);

	bool IsInitialize = false;

	void setLimitation(int x, int y, int width, int height);

	bool createStringMap();
protected:
	vector<Coordinate* > Positions;
	
	GameSprite* brick;
	LPDIRECT3DDEVICE9 graphic;

	int _start_x;
	int _start_y;
	int _limit_width;
	int _limit_height;
	string listString[290];
	int count;
	std::string fileName;

};