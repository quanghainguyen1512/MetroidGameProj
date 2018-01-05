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

	spriteManager = new SpriteManager();
	if (!spriteManager->Initialize("sprite.txt"))
	{
		return false;
	}

	map = new Map(0, 0, 0, 0, 0, NULL, spriteManager, gDevice);
	if (!map->Initialize(gDevice->device))
		return false;

	collisionManager = new CollisionManager(width, height);
	if (collisionManager)
	{
		collisionManager->ReadBrickData("leftofmap3.txt");
		collisionManager->ReadMonsterData("Monster1_2.txt");
		collisionManager->ReadRelation("Relation2.txt");
		map->ImportCollisionManager(collisionManager);
	}
	else
	{
		return false;
	}

	quadTree = new QuadTree(0, 0, 512, 512, 0, 0);
	if (quadTree)
	{
		quadTree->Initialize("QuadTree_leftofmap4.txt");
	}
	collisionManager->ImportQuadTree(quadTree);

	player = new Player(626, 3250, 0, 0.2f, 0.2f, collisionManager, spriteManager, gDevice);
	if (!player->Initialize(gDevice->device))
	{
		return false;
	}

	collisionManager->ImportPlayerCol(626, 3250, 14, 32);

	monsterManager = new MonsterManager(collisionManager, spriteManager, gDevice);
	if (monsterManager)
	{
		monsterManager->Initialize("Monster1_2.txt");
	}
	keyBoard = new KeyBoard(player);
	if (keyBoard->InitializeKeyBoard(hWnd, hInstance) == false)
		return false;

	camera = new Camera(width, height, 0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

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
	map->setLimitation(
		(player->GetPosition().x - (camera->getWidth() / 2)),
		((player->GetPosition().y - 32) - (camera->getHeight() / 2)),
		camera->getWidth(),
		camera->getHeight(),
		player->GetPosition().x,
		player->GetPosition().y);

	player->Update(gameTime);

	for (int i = 0; i < collisionManager->MonsterList.size(); i++)
	{
		monsterManager->update(collisionManager->MonsterList[i]);
	}

}

void Game::DrawMap()
{
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

	if (map&&map->IsInitialize == true)
	{
		DrawMap();
	}

	for (int i = 0; i < collisionManager->MonsterList.size(); i++)
	{
		monsterManager->draw(collisionManager->MonsterList[i]);
	}

	/*if (monsterManager)
	{
		monsterManager->drawAll();
	}*/

	if (player)
		player->Draw(gameTime);

	gDevice->End();
	gDevice->Present();

	collisionManager->resetList();
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
	else if (keyBoard->IsKeyDown(DIK_F))
		player->ProcessKey(GOD_MODE);
	else if (keyBoard->IsKeyDown(DIK_X))
		player->ProcessKey(JUMP_BUTTON);
	else if (keyBoard->IsKeyDown(DIK_Z))
		player->ProcessKey(SHOOT_BUTTON);
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
	if (map)
	{
		delete map;
		map = nullptr;
	}

}
