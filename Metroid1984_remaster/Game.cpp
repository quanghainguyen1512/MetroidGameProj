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

	player = new Player(626, 3297, 0, 0.15f, 0.15f);
	if (!player->Initialize(gDevice->device))
	{
		return false;
	}

	keyBoard = new KeyBoard();
	if (keyBoard->InitializeKeyBoard(hWnd, hInstance) == false)
		return false;

	camera = new Camera(width, height, 0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

	/*backGround = new BackGround(0, 0, 0, 0, 0);
	if (backGround->Initialize(gDevice->device) == false)
		return false;*/

<<<<<<< HEAD
	map = new Map(0, 3131, 0, 0, 0);
=======
	map = new Map(0, 0, 0, 0, 0);
>>>>>>> TheAnh
	if (!map->Initialize(gDevice->device))
		return false;

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
	camera->Follow(player);
	camera->Update();
	player->Update(gameTime);
}

void Game::DrawMap()
{
	map->setLimitation((player->GetPosition().x - (camera->getWidth() / 2)), ((player->GetPosition().y - 32) - (camera->getHeight() / 2)), camera->getWidth(), camera->getHeight());
	map->Draw(_gameTime);
}

void Game::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0, 0, 0));
	gDevice->Begin();

	if (camera)
	{
		camera->SetTransform(gDevice);
	}

	/*if (backGround&& backGround->is_initialize==true)
	{
		backGround->Draw(gameTime);
	}*/
	if (map&&map->IsInitialize == true)
	{
		DrawMap();
	}

	if (player)
		player->Draw(gameTime);

	gDevice->End();
	gDevice->Present();
}

void Game::ProcessController(HWND hWnd)
{
	keyBoard->ProcessKeyBoard(hWnd);
	ProcessInput();
}

void Game::ProcessInput()
{
	if (keyBoard->IsKeyDown(DIK_LEFT))
		player->ProcessKey(LEFT_ARROW);
	else if (keyBoard->IsKeyDown(DIK_RIGHT))
		player->ProcessKey(RIGHT_ARROW);
	else if (keyBoard->IsKeyDown(DIK_UP))
		player->ProcessKey(UP_ARROW);
	else if (keyBoard->IsKeyDown(DIK_DOWN))
		player->ProcessKey(DOWN_ARROW);
	else
		player->ProcessKey(UNKEY);
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

	if (camera)
	{
		delete camera;
		camera = nullptr;
	}

	/*if (backGround)
	{
		delete backGround;
		backGround = nullptr;
	}*/

	if (map)
	{
		delete map;
		map = nullptr;
	}

}
