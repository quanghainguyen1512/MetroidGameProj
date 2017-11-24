#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include<d3dx9.h>
#include<string>
#include"GraphicDevice.h"

class GameSprite
{
public:

	GameSprite();
	~GameSprite();

	bool initialize(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 tex, int XInTexture, int YInTexture, int width, int height, int count);
	bool IsInitialize();

	virtual void Update(float gameTime);
	virtual void Draw(float gameTime, D3DXVECTOR3 position);

private:
	LPDIRECT3DTEXTURE9 _tex;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	bool initialized;
	int index = 0;
	int start_x; int start_y;
	int _width; int _height;
	int x; int y;
	int _count;
};

#endif