#include"Field.h"

using namespace std;

Field::Field(float x, float y, float rotation, float speed, float maxSpeed, std::string file, LPDIRECT3DTEXTURE9 SourceTex) :
GameObject(x, y, rotation, speed, maxSpeed)
{
	fileName = file;
	tex = SourceTex;
}

bool Field::Initialize(LPDIRECT3DDEVICE9 device)
{
	graphic = device;
	if (Build_brick(device) == false)
		return false;
	return true;
}

bool Field::CreateTexture(LPDIRECT3DDEVICE9 device, std::string file)
{
	return true;
}

bool Field::Build_brick(LPDIRECT3DDEVICE9 device)
{
	int xInWorld = 0; int yInWorld = 0;
	std::ifstream file_txt(fileName);
	std::string str;
	std::string file_contents;
	while (std::getline(file_txt, str))
	{
		xInWorld = 0;
		char a[1024];
		strncpy_s(a, str.c_str(), sizeof(a));
		a[sizeof(a) - 1] = -1;
		for (int i = 0; i < sizeof(a); i++)
		{
			switch (a[i])
			{
			case '1':
			{
				Make_brick(device, 0, 0, xInWorld, yInWorld);
				break;
			}
			case '2':
			{
				Make_brick(device, 0, 1, xInWorld, yInWorld);
				break;
			}
			case '3':
			{
				Make_brick(device, 0, 2, xInWorld, yInWorld);
				break;
			}
			case '4':
			{
				Make_brick(device, 0, 3, xInWorld, yInWorld);
				break;
			}
			case '5':
			{
				Make_brick(device, 0, 4, xInWorld, yInWorld);
				break;
			}
			case '6':
			{
				Make_brick(device, 0, 5, xInWorld, yInWorld);
				break;
			}
			case '7':
			{
				Make_brick(device, 0, 6, xInWorld, yInWorld);
				break;
			}
			case '8':
			{
				Make_brick(device, 0, 7, xInWorld, yInWorld);
				break;
			}
			case '9':
			{
				Make_brick(device, 0, 8, xInWorld, yInWorld);
				break;
			}
			case 'a':
			{
				Make_brick(device, 0, 9, xInWorld, yInWorld);
				break;
			}
			case 'b':
			{
				Make_brick(device, 0, 10, xInWorld, yInWorld);
				break;
			}
			case 'c':
			{
				Make_brick(device, 0, 11, xInWorld, yInWorld);
				break;
			}
			case 'd':
			{
				Make_brick(device, 0, 12, xInWorld, yInWorld);

				break;
			}
			case 'e':
			{
				Make_brick(device, 0, 13, xInWorld, yInWorld);

				break;
			}
			case 'f':
			{
				Make_brick(device, 0, 14, xInWorld, yInWorld);

				break;
			}
			case 'g':
			{
				Make_brick(device, 0, 15, xInWorld, yInWorld);

				break;
			}
			case '0':
			{
				break;
			}
			case ' ':
			{
				xInWorld--;
				break;
			}
			default:
				break;
			}

			xInWorld++;
		}
		yInWorld++;
	}
	return true;
}
void Field::Make_brick(LPDIRECT3DDEVICE9 device, int columnInSource, int rowInSource, int xInWorld, int yInWorld)
{
	Coordinate* c = new Coordinate(columnInSource * 16, rowInSource * 16, xInWorld * 16 + position.x, yInWorld * 16 + position.y);
	Positions.push_back(c);
}

void Field::Draw(float gameTime)
{
	brick = new GameSprite();
	if (brick->initialize(graphic, tex, Positions[0]->_xInTexture, Positions[0]->_yInTexture, 16, 16, 1))
	{
		for (int i = 0; i < Positions.size(); i++)
		{
			if (Positions[i]->_xInWorld >= _start_x - 16 && Positions[i]->_xInWorld <= (_start_x + _limit_width) && Positions[i]->_yInWorld >= _start_y - 16 && Positions[i]->_yInWorld <= (_start_y + _limit_height))
			{
				brick->Draw(Positions[i]->_xInTexture, Positions[i]->_yInTexture, 16, 16, D3DXVECTOR3(Positions[i]->_xInWorld, Positions[i]->_yInWorld, 0));
			}
		}
	}
	delete brick;
	brick = nullptr;
}

void Field::setLimitation(int x, int y, int width, int height)
{
	_start_x = x;
	_start_y = y;
	_limit_width = width;
	_limit_height = height;
}

void Field::Update(float gameTime)
{

}

Field::~Field()
{
	/*if (brick)
	{
		delete brick;
		brick = nullptr;
	}*/
}