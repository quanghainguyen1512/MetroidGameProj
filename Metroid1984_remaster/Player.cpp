#include"Player.h"

Player::Player(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager)
{
	velocity.y = 0.15f;
}

bool Player::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;

	if (!CreateTexture(device, FILE))
		return false;

	if (!Right_move)
	{
		Right_move = new GameSprite();
		if (!Right_move->initialize(device, tex, RIGHT_MOVE_X, RIGHT_MOVE_Y, NORMAL_WIDTH, NORMAL_HEIGHT, RUN_COUNT))
		{
			return false;
		}
	}

	if (!Left_move)
	{
		Left_move = new GameSprite();
		if (!Left_move->initialize(device, tex, LEFT_MOVE_X, LEFT_MOVE_Y, NORMAL_WIDTH, NORMAL_HEIGHT, RUN_COUNT))
		{
			return false;
		}
	}

	if (!Right_jump)
	{
		Right_jump = new GameSprite();
		if (!Right_jump->initialize(device, tex, RIGHT_JUMP_X, RIGHT_JUMP_Y, NORMAL_WIDTH, NORMAL_HEIGHT, JUMP_COUNT))
		{
			return false;
		}
	}
	if (!Left_jump)
	{
		Left_jump = new GameSprite();
		if (!Left_jump->initialize(device, tex, LEFT_JUMP_X, LEFT_JUMP_Y, NORMAL_WIDTH, NORMAL_HEIGHT, JUMP_COUNT))
		{
			return false;
		}
	}
	if (!Right_jump_spin)
	{
		Right_jump_spin = new GameSprite();
		if (!Right_jump_spin->initialize(device, tex, RIGHT_JUMP_SPIN_X, RIGHT_JUMP_SPIN_Y, NORMAL_WIDTH, NORMAL_HEIGHT, JUMP_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Left_jump_spin)
	{
		Left_jump_spin = new GameSprite();
		if (!Left_jump_spin->initialize(device, tex, LEFT_JUMP_SPIN_X, LEFT_JUMP_SPIN_Y, NORMAL_WIDTH, GSPIN_SIZE, JUMP_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Right_ground_spin)
	{
		Right_ground_spin = new GameSprite();
		if (!Right_ground_spin->initialize(device, tex, RIGHT_GROUND_SPIN_X, RIGHT_GROUND_SPIN_Y, NORMAL_WIDTH, GSPIN_SIZE, GROUND_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Left_ground_spin)
	{
		Left_ground_spin = new GameSprite();
		if (!Left_ground_spin->initialize(device, tex, LEFT_GROUND_SPIN_X, LEFT_GROUND_SPIN_Y, NORMAL_WIDTH, NORMAL_HEIGHT, GROUND_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Right_stand)
	{
		Right_stand = new GameSprite();
		if (!Right_stand->initialize(device, tex, RIGHT_STAND_X, RIGHT_STAND_Y, NORMAL_WIDTH, NORMAL_HEIGHT, STAND_COUNT))
		{
			return false;
		}
	}

	if (!Left_stand)
	{
		Left_stand = new GameSprite();
		if (!Left_stand->initialize(device, tex, LEFT_STAND_X, LEFT_STAND_Y, NORMAL_WIDTH, NORMAL_HEIGHT, STAND_COUNT))
		{
			return false;
		}
	}

	Is_initialzed = true;
	spriteID = 4; 
	ActionID = 2;
	return true;
}

bool Player::CreateTexture(LPDIRECT3DDEVICE9 device, std::string file)
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
	return true;
}

bool Player::InitializeFlag()
{
	return Is_initialzed;
}

void Player::Update(float gameTime)
{
	if (status == ObjectStatus::Active)
	{
		float tempx = position.x;
		float tempy = position.y;

		tempx += velocity.x*(gameTime)*direction;
		tempy += velocity.y*(gameTime);
		position.z = 0;
		if (last_direction == 1)
		{
			if (Is_jump == true)
			{
				Right_jump->Update(gameTime);
				spriteID = 0;
				ActionID = 2;
				spriteWidth = 23;
				spriteHeight = 25;
				Is_air = true;
			}
			else if (Is_fall == true && direction != 0)
			{
				Right_jump_spin->Update(gameTime);
				spriteID = 1;
				ActionID = 2;
				spriteWidth = 19;
				spriteHeight = 19;
				Is_air = true;
			}
			else if (Is_ground_spin == true)
			{
				Right_ground_spin->Update(gameTime);
				spriteID = 2;
				ActionID = 0;
				spriteWidth = 13;
				spriteHeight = 13;
			}
			else if (direction != 0)
			{
				Right_move->Update(gameTime);
				spriteID = 3;
				ActionID = 0;
				spriteWidth = 14;
				spriteHeight =20;
			}
			else if (Is_stand == true)
			{
				Right_stand->Update(gameTime);
				spriteID = 4;
				ActionID = 3;
				spriteWidth = 14;
				spriteHeight = 20;
			}
		}
		if (last_direction == -1)
		{
			if (Is_jump == true)
			{
				Left_jump->Update(gameTime);
				spriteID = 0;
				ActionID = 2;
				spriteWidth = 23;
				spriteHeight = 25;
				Is_air = true;
			}
			else if (Is_fall == true && direction != 0)
			{
				Left_jump_spin->Update(gameTime);
				spriteID = 1;
				ActionID = 2;
				spriteWidth = 19;
				spriteHeight = 19;
				Is_air = true;
			}
			else if (Is_ground_spin == true)
			{
				Left_ground_spin->Update(gameTime);
				spriteID = 2;
				ActionID = 1;
				spriteWidth = 13;
				spriteHeight = 13;
			}
			else if (direction != 0)
			{
				Left_move->Update(gameTime);
				spriteID = 3;
				ActionID = 1;
				spriteWidth = 14;
				spriteHeight = 20;
			}
			else if (Is_stand == true)
			{
				Left_stand->Update(gameTime);
				spriteID = 4;
				ActionID = 3;
				spriteWidth = 14;
				spriteHeight = 20;
			}
		}
		_collisionManager->UpdatePlayerCol(tempx, tempy, spriteWidth, spriteHeight, velocity.x*direction, velocity.y);

		float remainTimeX = _collisionManager->RemainXtime(position.x, velocity.x*direction);
		float remainTimeY = _collisionManager->RemainYtime(position.y, velocity.y);
		
		if (remainTimeX > 0)
			position.x += velocity.x*(gameTime - remainTimeX)*direction;
			//position.x -= velocity.x*(gameTime)*direction;
		else
			position.x += velocity.x*(gameTime)*direction;
		
		if (remainTimeY > 0)
			position.y += velocity.y*(gameTime - remainTimeY);
			//position.y -= velocity.y*(gameTime);
		else
			position.y += velocity.y*(gameTime);

		/*position.x += velocity.x*(gameTime - remainTimeX)*direction;
		position.y += velocity.y*(gameTime - remainTimeY);*/


		_collisionManager->UpdatePlayerCol(tempx, tempy, spriteWidth, spriteHeight, velocity.x*direction, velocity.y);
	}
}

void Player::Draw(float gameTime)
{
	if (last_direction == 1)
	{
		switch (spriteID)
		{
		case 0:
		{
			Right_jump->Draw(gameTime, position);
			break;
		}
		case 1:
		{
			Right_jump_spin->Draw(gameTime, position);
			break;
		}
		case 2:
		{
			Right_ground_spin->Draw(gameTime, position);
			break;
		}
		case 3:
		{
			Right_move->Draw(gameTime, position);
			break;
		}
		case 4:
		{
			Right_stand->Draw(gameTime, position);
			break;
		}
		default:
			break;
		}
	}
	if (last_direction == -1)
	{
		switch (spriteID)
		{

		case 0:
		{
			Left_jump->Draw(gameTime, position);
			break;
		}
		case 1:
		{
			Left_jump_spin->Draw(gameTime, position);
			break;
		}
		case 2:
		{
			Left_ground_spin->Draw(gameTime, position);
			break;
		}
		case 3:
		{
			Left_move->Draw(gameTime, position);
			break;
		}
		case 4:
		{
			Left_stand->Draw(gameTime, position);
			break;
		}
		default:
			break;
		}
	}
}

Player::~Player()
{
	if (Right_move)
	{
		delete Right_move;
		Right_move = 0;
	}
	if (Left_move)
	{
		delete Left_move;
		Left_move = 0;
	}
	if (Right_jump)
	{
		delete Right_jump;
		Right_jump = 0;
	}
	if (Left_jump)
	{
		delete Left_jump;
		Left_jump = 0;
	}
	if (Right_jump_spin)
	{
		delete Right_jump_spin;
		Right_jump_spin = 0;
	}
	if (Left_jump_spin)
	{
		delete Left_jump_spin;
		Left_jump_spin = 0;
	}
	if (Right_ground_spin)
	{
		delete Right_ground_spin;
		Right_ground_spin = 0;
	}
	if (Left_ground_spin)
	{
		delete Left_ground_spin;
		Left_ground_spin = 0;
	}
}

D3DXVECTOR3 Player::GetPosition()
{
	return position;
}

void Player::OnKeyDown(int keyCode)
{

}

void Player::OnKeyUp(int keyCode)
{

}

void Player::ProcessKey(int keyDown)
{
	switch (keyDown)
	{
	case LEFT_ARROW:
	{
		direction = -1;
		last_direction = direction;
	}break;
	case RIGHT_ARROW:
	{
		direction = 1;
		last_direction = direction;
	}break;
	case UP_ARROW:
	{
		if (Is_ground_spin != false)
		{
			Is_ground_spin = false;
			position.y = position.y - 20;
		}
	}break;
	case DOWN_ARROW:
	{
		if (Is_ground_spin != true)
		{
			Is_ground_spin = true;
			position.y = position.y + 20;
		}
	}break;
	case UNKEY:
	{
		direction = 0;
	}
	default:
	{

	}
	break;
	}
}