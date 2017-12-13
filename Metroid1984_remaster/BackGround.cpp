#include"BackGround.h"

BackGround::BackGround(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager)
{

}

bool BackGround::Initialize(LPDIRECT3DDEVICE9 device)
{
	if (CreateTexture(device, "LV1_main.png")==false)
		return false;

	if (!image)
	{
		image = new GameSprite();
		if (!image->initialize(device, tex, 0, 0, 7680, 4560, 1))
		{
			return false;
		}
	}

	is_initialize = true;

	return true;
}

bool BackGround::CreateTexture(LPDIRECT3DDEVICE9 device, std::string file)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(file.c_str(), &info);

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

	return true;
}


void BackGround::Update(float gameTime){}

void BackGround::Draw(float gameTime)
{
	image->Draw(gameTime, position);
}

BackGround::~BackGround()
{
	if (image)
	{
		delete image;
		image = nullptr;
	}
}