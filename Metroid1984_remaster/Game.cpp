#include"Game.h"

Game::Game()
{

}

bool Game::Initialize(HWND hWnd, HINSTANCE hInstance, int width, int height)
{
	gDevice = new GraphicsDevice();
	if (!gDevice->Initialize(hWnd, true))
	{
		return false;
	}

	GO = new GameObject(110, 110, 0, 0, 0);
	if (!GO->Initialize(gDevice->device, "Metroid_sprite_motion_2.png"))
	{
		return false;
	}

	_width = width;
	_height = height;


	return true;
}

void Game::Run(float gameTime)
{
	//chay ham Update va Draw
	Update(gameTime);
	Draw(gameTime);
}

void Game::Update(float gameTime)
{
	_gameTime = gameTime;
	GO->Update(gameTime);
}

void Game::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 100));
	gDevice->Begin();

	GO->Draw(gameTime);

	gDevice->End();
	gDevice->Present();
}
Game::~Game()
{
	if (GO)
	{
		delete GO;
		GO = nullptr;
	}

	if (gDevice)
	{
		delete gDevice;
		gDevice = nullptr;
	}

}
