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

	player = new Player(0, 0, 0, 100.0f, 100.0f);
	if (!player->Initialize(gDevice->device))
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
	player->Update(gameTime);
}

void Game::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0, 0, 0));
	gDevice->Begin();

	if (player)
		player->Draw(gameTime);

	gDevice->End();
	gDevice->Present();
}
Game::~Game()
{
	if (player)
	{
		delete player;
		player = nullptr;
	}

	if (gDevice)
	{
		delete gDevice;
		gDevice = nullptr;
	}

}
