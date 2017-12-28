#ifndef PLAYER_H
#define PLAYER_H

#include"GamePlayObject.h"

class Player : public GameObject
{
public:
	Player(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spritemanager);
	~Player();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);
	bool CreateTexture(LPDIRECT3DDEVICE9 device, std::string file);

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void ProcessKey(int keyDown);

	bool InitializeFlag();
	D3DXVECTOR3 GetPosition();

	void UpdateBehavior();
	void jump();

protected:

	GameSprite* Right_move;
	GameSprite* Left_move;
	GameSprite* Right_jump;
	GameSprite* Left_jump;
	GameSprite* Right_jump_spin;
	GameSprite* Left_jump_spin;
	GameSprite* Right_ground_spin;
	GameSprite* Left_ground_spin;
	GameSprite* Right_stand;
	GameSprite* Left_stand;

	bool Is_initialzed = false;
	bool Is_jump = false;
	bool Is_fall = false;
	bool Is_run = false;
	bool Is_ground_spin = false;
	bool Is_stand = true;
	bool Is_air = true;

	float directionX = 0;
	float last_directionX = 1;
	float directionY = 1;
	float last_directionY = 1;

	int ActionID;
	int spriteID;

	int spriteWidth;
	int spriteHeight;
	int lastWidth;
	int lastHeight;

	string collisionXTag;
	string collisionYTag;

	int height_limited;
};

#endif