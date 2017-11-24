#include"GameSprite.h"

GameSprite::GameSprite()
{
	//gan gia tri cho color ( he mau trong suot )

	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	initialized = false;
}


bool GameSprite::initialize(LPDIRECT3DDEVICE9 device, LPDIRECT3DTEXTURE9 tex , int XInTexture, int yInTexture, int width, int height, int count)
{
	//Lay thong tin tu file hinh goc

	_tex = tex;
	start_x = XInTexture;
	start_y = yInTexture;
	_width = width;
	_height = height;
	_count = count;
	// khoi tao Texture

	if (!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "file not found", NULL, NULL);
		return false;
	}

	initialized = true;

	return true;
}

bool GameSprite::IsInitialize()
{
	return initialized;
}

void GameSprite::Update(float gameTime)
{
	//cap nhap sprite de co chuyen dong

	x = start_x + index*_width;
	y = start_y;
	index++;
	if (index == _count)
		index = 0;
}

void GameSprite::Draw(float gameTime, D3DXVECTOR3 position)
{
	//ve sprite the tham so da cap nhap

	if (sprite && _tex)
	{
		RECT srect;
		srect.left = x;
		srect.top = y;
		srect.right = srect.left + _width;
		srect.bottom = srect.top + _height;

		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(_tex, &srect, NULL, &position, color);
		sprite->End();
	}
}

GameSprite::~GameSprite()
{
	if (sprite)
	{
		sprite->Release();
		sprite = 0;
	}
	if (_tex)
	{
		_tex->Release();
		_tex = 0;
	}
}