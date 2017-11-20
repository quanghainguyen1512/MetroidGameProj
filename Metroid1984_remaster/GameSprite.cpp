#include"GameSprite.h"

GameSprite::GameSprite()
{
	//gan gia tri cho color ( he mau trong suot )

	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	initialized = false;
}


bool GameSprite::initialize(LPDIRECT3DDEVICE9 device, std::string file, int XInTexture, int yInTexture, int width, int height, int count)
{
	//Lay thong tin tu file hinh goc

	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(file.c_str(), &info);

	start_x = XInTexture;
	start_y = yInTexture;
	_width = width;
	_height = height;
	_count = count;

	// khoi tao Texture
	
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(
		device,
		file.c_str(),
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&tex)))
	{
		std::string s = "Make sure the file exist and path is right. Requested Image: " + file;
		MessageBox(NULL, s.c_str(), NULL, NULL);
		return false;
	}

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

	if (sprite && tex)
	{
		RECT srect;
		srect.left = x;
		srect.top = y;
		srect.right = srect.left + _width;
		srect.bottom = srect.top + _height;

		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(tex, &srect, NULL, &position, color);
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
	if (tex)
	{
		tex->Release();
		tex = 0;
	}
}