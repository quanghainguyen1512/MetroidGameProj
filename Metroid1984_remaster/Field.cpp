#include"Field.h"

using namespace std;

Field::Field(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, std::string file, LPDIRECT3DTEXTURE9 SourceTex, SpriteManager* spriteManager) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager,spriteManager)
{
	fileName = file;
	tex = SourceTex;
	count = 0;
}

bool Field::Initialize(LPDIRECT3DDEVICE9 device)
{
	graphic = device;
	if (createStringMap() == false)
		return false;
	return true;
}

bool Field::CreateTexture(LPDIRECT3DDEVICE9 device, std::string file)
{
	return true;
}

bool Field::createStringMap()
{
	std::ifstream file_txt(fileName);
	std::string str;
	
	while (std::getline(file_txt,str))
	{
		listString[count] = str;
		count++;
	}

	return true;
}

void Field::Draw(float gameTime)
{
	brick = new GameSprite(_spriteManager);
	if (brick->initialize(graphic, tex, BRICK, 1))
	{
		int x = _start_x - position.x;
		int y = _start_y - position.y;
		int x16Pixel = x / 16;
		int y16Pixel = y / 16;
		
		for (int i = y16Pixel; i < y16Pixel + 16; i++)
		{
			char a[1024];
			strncpy_s(a, listString[i].c_str(), sizeof(a));
			a[sizeof(a) - 1] = -1;
			for (int j = x16Pixel; j < x16Pixel + 17; j++)
			{
				char b = a[j];
				switch (b)
				{
				case '1':
				{
					brick->Draw(0, 0, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case '2':
				{
					brick->Draw(0, 16, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case '3':
				{
					brick->Draw(0, 32, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case '4':
				{
					brick->Draw(0, 48, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case '5':
				{
					brick->Draw(0, 64, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case '6':
				{
					brick->Draw(0, 80, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case '7':
				{
					brick->Draw(0, 96, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case '8':
				{
					brick->Draw(0, 112, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case '9':
				{
					brick->Draw(0, 128, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'a':
				{
					brick->Draw(0, 144, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'b':
				{
					brick->Draw(0, 160, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'c':
				{
					brick->Draw(0, 176, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'd':
				{
					brick->Draw(0, 192, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));

					break;
				}
				case 'e':
				{
					brick->Draw(0, 224, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'f':
				{
					brick->Draw(0, 240, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));

					break;
				}
				case 'g':
				{
					brick->Draw(0, 256, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'h':
				{
					brick->Draw(0, 270, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'i':
				{
					brick->Draw(0, 288, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'k':
				{
					brick->Draw(0, 304, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'l':
				{
					brick->Draw(0, 320, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'm':
				{
					brick->Draw(0, 336, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'n':
				{
					brick->Draw(0, 352, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'o':
				{
					brick->Draw(0, 368, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'p':
				{
					brick->Draw(0, 384, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'q':
				{
					brick->Draw(0, 400, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'r':
				{
					brick->Draw(0, 416, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 's':
				{
					brick->Draw(0, 432, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 't':
				{
					brick->Draw(0, 448, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'u':
				{
					brick->Draw(0, 464, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'v':
				{
					brick->Draw(0, 480, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'w':
				{
					brick->Draw(0, 496, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'x':
				{
					brick->Draw(0, 512, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'y':
				{
					brick->Draw(0, 528, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'z':
				{
					brick->Draw(0, 544, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'A':
				{
					brick->Draw(0, 560, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'B':
				{
					brick->Draw(0, 576, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'C':
				{
					brick->Draw(0, 592, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'D':
				{
					brick->Draw(0, 608, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'E':
				{
					brick->Draw(0, 624, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'F':
				{
					brick->Draw(0, 640, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'G':
				{
					brick->Draw(0, 656, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'H':
				{
					brick->Draw(0, 672, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'I':
				{
					brick->Draw(0, 688, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'K':
				{
					brick->Draw(0, 704, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'L':
				{
					brick->Draw(0, 720, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'M':
				{
					brick->Draw(0, 736, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'N':
				{
					brick->Draw(0, 752, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'O':
				{
					brick->Draw(0, 768, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'P':
				{
					brick->Draw(0, 784, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'Q':
				{
					brick->Draw(0, 800, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'R':
				{
					brick->Draw(0, 816, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'S':
				{
					brick->Draw(0, 832, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case 'T':
				{
					brick->Draw(0, 848, 16, 16, D3DXVECTOR3(j * 16 + position.x, i * 16 + position.y, 0));
					break;
				}
				case '0':
				{
					break;
				}
				default:
					break;
				}
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