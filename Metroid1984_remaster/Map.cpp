#include"Map.h"

using namespace std;

Map::Map(float x, float y, float rotation, float speed, float maxSpeed) :
GameObject(x, y, rotation, speed, maxSpeed)
{

}

bool Map::Initialize(LPDIRECT3DDEVICE9 device)
{
	if (CreateTexture(device, "a2.png") == false)
		return false;

	field1 = new Field(0, 3136, 0, 0, 0, "field1.txt",tex);
	if (field1->Initialize(device)==false)
	{
		return false;
	}
	field2 = new Field(1248, 3136, 0, 0, 0, "field2.txt",tex);
	if (field2->Initialize(device) == false)
	{
		return false;
	}
	field3 = new Field(1504, 3056, 0, 0, 0, "field3.txt",tex);
	if (field3->Initialize(device) == false)
	{
		return false;
	}
	field4 = new Field(2560, 3056, 0, 0, 0, "field4.txt",tex);
	if (field4->Initialize(device) == false)
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
	switch (field_flag)
	{
	case 1:
	{
		field1->Draw(gameTime);
		break;
	}
	case 2:
	{
		field2->Draw(gameTime);
		break;
	}
	case 3:
	{
		field3->Draw(gameTime);
		break;
	}
	case 4 :
	{
		field4->Draw(gameTime);
		break;
	}
	default:
		break;
	}
}

void Map::setLimitation(int x, int y, int width, int height)
{
	if ((x + width / 2)>field1->getPosition().x && (x + width / 2) <= field2->getPosition().x)
	{
		field1->setLimitation(x, y, width, height);
		field_flag = 1;
	}
	else if ((x + width / 2)>field2->getPosition().x && (x + width / 2) <= field3->getPosition().x)
	{
		field2->setLimitation(x, y, width, height);
		field_flag = 2;
	}
	else if ((x + width / 2)>field3->getPosition().x && (x + width / 2) <= field4->getPosition().x)
	{
		field3->setLimitation(x, y, width, height);
		field_flag = 3;
	}
	else if ((x + width / 2)>field4->getPosition().x)
	{
		field4->setLimitation(x, y, width, height);
		field_flag = 4;
	}
}

void Map::Update(float gameTime)
{

}

Map::~Map()
{
	if (field1)
	{
		delete field1;
		field1 = nullptr;
	}
	if (field2)
	{
		delete field2;
		field2 = nullptr;
	}
	if (field3)
	{
		delete field3;
		field3 = nullptr;
	}
	if (field4)
	{
		delete field4;
		field4 = nullptr;
	}
}