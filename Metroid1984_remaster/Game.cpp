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
}

void Game::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 100));
	gDevice->Begin();
	gDevice->End();
	gDevice->Present();
}
Game::~Game()
{
	if (gDevice)
	{
		delete gDevice;
		gDevice = nullptr;
	}
}
