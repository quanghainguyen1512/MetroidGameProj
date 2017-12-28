#ifndef BACKGROUND_H
#define BACKGROUND_H

#include"GamePlayObject.h"

class BackGround :public GameObject
{
public:
	BackGround(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager,SpriteManager* spriteManager);
	~BackGround();

	bool Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float gameTime);
	void Draw(float gameTime);
	bool CreateTexture(LPDIRECT3DDEVICE9 device, std::string file);

	bool is_initialize = false;
private:
	

	GameSprite* image;

};

#endif