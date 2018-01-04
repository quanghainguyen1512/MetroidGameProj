#ifndef GAME_H
#define GAME_H

#include"GraphicDevice.h"
#include<dinput.h>
#include"GamePlayObject.h"
#include"Player.h"
#include"KeyBoard.h"
#include"Camera.h"
#include"BackGround.h"
#include"Map.h"
#include"CollisionManager.h"
#include"QuadTree.h"
#include"MonsterManager.h"

#define KEYBOARD_BUFFER_SIZE 1024

class Game
{
public:
	Game();
	~Game();

	bool Initialize(HWND hWnd, HINSTANCE hInstance, int width, int height);
	void Run(float gameTime);
	void Update(float gameTime);
	void Draw(float gameTime);

	void DrawMap();
	void ProcessController(HWND hWnd);
	void ProcessInput();

private:
	GraphicsDevice *gDevice;

	int _width;
	int _height;

	float _gameTime;

	Player* player;

	KeyBoard* keyBoard;

	Camera* camera;

	Map* map;

	CollisionManager* collisionManager;

	SpriteManager* spriteManager;

	QuadTree* quadTree;

	MonsterManager* monsterManager;

};

#endif GAME_H