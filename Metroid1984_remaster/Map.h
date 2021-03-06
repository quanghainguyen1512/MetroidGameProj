#include"GamePlayObject.h"
#include"Coordinate.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"Field.h"

using namespace std;

class Map :public GameObject
{
public:
	Map(
		float x, 
		float y, 
		float rotation, 
		float speed, 
		float maxSpeed, 
		CollisionManager* collisionManager, 
		SpriteManager* spriteManager, 
		GraphicsDevice* gDevice);
	~Map();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);

	bool IsInitialize = false;

	void setLimitation(int x, int y, int width, int height, int playerX, int playerY);
	void ImportCollisionManager(CollisionManager* c);

protected:
	Field* halfofmap_left;

	bool Build_brick(LPDIRECT3DDEVICE9 device);
	void Make_brick(LPDIRECT3DDEVICE9 device, int columnInSource, int rowInSource, int xInWorld, int yInWorld);
	
	LPDIRECT3DDEVICE9 graphic;

	int _start_x;
	int _start_y;
	int _limit_width;
	int _limit_height;

	int _player_x;
	int _player_y;
	int _Player_height;
	int _Player_width;

	bool setComplete;

	int field_flag;
};