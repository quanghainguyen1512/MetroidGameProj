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

	map = new Map(0, 0, 0, 0, 0, NULL);
	if (!map->Initialize(gDevice->device))
		return false;

	collisionManager = new CollisionManager();
	if (collisionManager)
	{
		collisionManager->ImportCollision(19, 207, 16, 16, "brick");
		collisionManager->ImportCollision(19, 208, 32, 16, "brick");
		collisionManager->ImportCollision(22, 206, 16, 48, "brick");
		collisionManager->ImportCollision(24, 208, 32, 16, "brick");
		collisionManager->ImportCollision(25, 207, 16, 16, "brick");

		collisionManager->ImportCollision(26, 200, 64, 16, "brick");
		collisionManager->ImportCollision(27, 201, 80, 32, "brick");
		collisionManager->ImportCollision(28, 203, 90, 16, "brick");
		collisionManager->ImportCollision(29, 204, 80, 32, "brick");
		collisionManager->ImportCollision(28, 206, 64, 32, "brick");

		collisionManager->ImportCollision(37, 199, 16, 32, "brick");
		collisionManager->ImportCollision(37, 201, 32, 64, "brick");
		collisionManager->ImportCollision(41, 199, 16, 32, "brick");
		collisionManager->ImportCollision(42, 201, 36, 64, "brick");

		collisionManager->ImportCollision(37, 207, 112, 16, "brick");
		collisionManager->ImportCollision(16, 208, 976, 32, "brick");
	}

	player = new Player(626, 3250, 0, 0.15f, 0.15f, collisionManager);
	if (!player->Initialize(gDevice->device))
	{
		return false;
	}

	collisionManager->ImportPlayerCol(626, 3250, 14, 32);

	keyBoard = new KeyBoard();
	if (keyBoard->InitializeKeyBoard(hWnd, hInstance) == false)
		return false;

	camera = new Camera(width, height, 0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

	/*backGround = new BackGround(0, 0, 0, 0, 0);
	if (backGround->Initialize(gDevice->device) == false)
		return false;*/

	

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
