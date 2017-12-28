#include"Map.h"

using namespace std;

Map::Map(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spriteManager) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager,spriteManager)
{

}

bool Map::Initialize(LPDIRECT3DDEVICE9 device)
{
	if (CreateTexture(device, "a2.png") == false)
		return false;

	halfofmap_left = new Field(0, 16, 0, 0, 0, NULL, "halfofmap_left.txt", tex, _spriteManager);
	if (halfofmap_left->Initialize(device) == false)
	{
		return false;
	}
	IsInitialize = true;
	return true;
}

bool Map::CreateTexture(LPDIRECT3DDEVICE9 device, std::string file)
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
	graphic = device;
	return true;
}


void Map::Draw(float gameTime)
{
	halfofmap_left->Draw(gameTime);
}

void Map::setLimitation(int x, int y, int width, int height)
{
	halfofmap_left->setLimitation(x, y, width, height);
}

void Map::Update(float gameTime)
{

}

Map::~Map()
{
	if (halfofmap_left)
	{
		delete halfofmap_left;
		halfofmap_left = nullptr;
	}
}