#include"Player.h"

Player::Player(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spritemanager, GraphicsDevice* gDevice) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager, spritemanager, gDevice)
{
	velocity.y = 0.15f;
}

bool Player::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;

	if (!Right_move)
	{
		Right_move = new GameSprite(_spriteManager);
		if (!Right_move->initialize(device, _gDevice->getCharaterTex(), RIGHT_MOVE_INDEX, RUN_COUNT))
		{
			return false;
		}
	}

	if (!Left_move)
	{
		Left_move = new GameSprite(_spriteManager);
		if (!Left_move->initialize(device, _gDevice->getCharaterTex(), LEFT_MOVE_INDEX, RUN_COUNT))
		{
			return false;
		}
	}

	if (!Right_jump)
	{
		Right_jump = new GameSprite(_spriteManager);
		if (!Right_jump->initialize(device, _gDevice->getCharaterTex(), RIGHT_JUMP_INDEX, JUMP_COUNT))
		{
			return false;
		}
	}
	if (!Left_jump)
	{
		Left_jump = new GameSprite(_spriteManager);
		if (!Left_jump->initialize(device, _gDevice->getCharaterTex(), LEFT_JUMP_INDEX, JUMP_COUNT))
		{
			return false;
		}
	}
	if (!Right_jump_spin)
	{
		Right_jump_spin = new GameSprite(_spriteManager);
		if (!Right_jump_spin->initialize(device, _gDevice->getCharaterTex(), RIGHT_JUMP_SPIN_INDEX, JUMP_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Left_jump_spin)
	{
		Left_jump_spin = new GameSprite(_spriteManager);
		if (!Left_jump_spin->initialize(device, _gDevice->getCharaterTex(), LEFT_JUMP_SPIN_INDEX, JUMP_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Right_ground_spin)
	{
		Right_ground_spin = new GameSprite(_spriteManager);
		if (!Right_ground_spin->initialize(device, _gDevice->getCharaterTex(), RIGHT_GROUND_SPIN_INDEX, GROUND_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Left_ground_spin)
	{
		Left_ground_spin = new GameSprite(_spriteManager);
		if (!Left_ground_spin->initialize(device, _gDevice->getCharaterTex(), LEFT_GROUND_SPIN_INDEX, GROUND_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Right_stand)
	{
		Right_stand = new GameSprite(_spriteManager);
		if (!Right_stand->initialize(device, _gDevice->getCharaterTex(), RIGHT_STAND_INDEX, STAND_COUNT))
		{
			return false;
		}
	}

	if (!Left_stand)
	{
		Left_stand = new GameSprite(_spriteManager);
		if (!Left_stand->initialize(device, _gDevice->getCharaterTex(), LEFT_STAND_INDEX, STAND_COUNT))
		{
			return false;
		}
	}

	Is_initialzed = true;
	spriteID = 4; 
	ActionID = 2;

	spriteWidth = Right_stand->getWidth();
	spriteHeight = Right_stand->getHeight();

	collisionXTag = "";
	collisionYTag = "";
	MonsterXTag = "";
	MonsterYTag = "";

	height_limited = position.y - 50;
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
		lastHeight = spriteHeight;
		lastWidth = spriteWidth;

		if (Is_jump == true && Is_air == true)
		{
			directionY += 0.15;
			if (directionY >= 0 && Is_stand == false)
				Is_fall = true;
		}

		tempx += velocity.x*(gameTime)*directionX;
		tempy += velocity.y*(gameTime)*directionY;
		position.z = 0;

		if (last_directionX == 1)
		{
			if ((Is_jump == true || Is_air == true) && Is_ground_spin == false && (directionX == 0))
			{
				Right_jump->Update(gameTime);
				spriteID = 0;
				ActionID = 2;
				spriteWidth = Right_jump->getWidth();
				spriteHeight = Right_jump->getHeight();
				//Is_air = true;
			}
			else if (Is_fall == true && directionX != 0 && Is_air == true && directionY > 0)
			{
				Right_jump_spin->Update(gameTime);
				spriteID = 1;
				ActionID = 2;
				spriteWidth = Right_jump_spin->getWidth();
				spriteHeight = Right_jump_spin->getHeight();
				//Is_air = true;
			}
			else if (Is_ground_spin == true)
			{
				Right_ground_spin->Update(gameTime);
				spriteID = 2;
				ActionID = 0;
				spriteWidth = Right_ground_spin->getWidth();
				spriteHeight = Right_ground_spin->getHeight();
			}
			else if (directionX != 0 && Is_air == false)
			{
				Right_move->Update(gameTime);
				spriteID = 3;
				ActionID = 0;
				spriteWidth = Right_move->getWidth();
				spriteHeight = Right_move->getHeight();
			}
			else if (Is_stand == true)
			{
				Right_stand->Update(gameTime);
				spriteID = 4;
				ActionID = 3;
				spriteWidth = Right_stand->getWidth();
				spriteHeight = Right_stand->getHeight();
			}
		}
		if (last_directionX == -1)
		{
			if ((Is_jump == true || Is_air == true) && Is_ground_spin == false && (directionX == 0))
			{
				Left_jump->Update(gameTime);
				spriteID = 0;
				ActionID = 2;
				spriteWidth = Left_jump->getWidth();
				spriteHeight = Left_jump->getHeight();
				//Is_air = true;
			}
			else if (Is_fall == true && directionX != 0 && Is_air == true && directionY > 0)
			{
				Left_jump_spin->Update(gameTime);
				spriteID = 1;
				ActionID = 2;
				spriteWidth = Left_jump_spin->getWidth();
				spriteHeight = Left_jump_spin->getHeight();
				//Is_air = true;
			}
			else if (Is_ground_spin == true)
			{
				Left_ground_spin->Update(gameTime);
				spriteID = 2;
				ActionID = 1;
				spriteWidth = Left_ground_spin->getWidth();
				spriteHeight = Left_ground_spin->getHeight();
			}
			else if (directionX != 0 && Is_air == false)
			{
				Left_move->Update(gameTime);
				spriteID = 3;
				ActionID = 1;
				spriteWidth = Left_move->getWidth();
				spriteHeight = Left_move->getHeight();
			}
			else if (Is_stand == true)
			{
				Left_stand->Update(gameTime);
				spriteID = 4;
				ActionID = 3;
				spriteWidth = Left_stand->getWidth();
				spriteHeight = Left_stand->getHeight();
			}
		}
		_collisionManager->UpdatePlayerCol(tempx, tempy, spriteWidth, spriteHeight, velocity.x*directionX, velocity.y*directionY);

		float remainTimeX = _collisionManager->RemainXtime(position.x, lastWidth, velocity.x*directionX, collisionXTag, MonsterXTag);
		float remainTimeY = _collisionManager->RemainYtime(position.y, lastHeight, velocity.y*directionY, collisionYTag, MonsterYTag);

		if (remainTimeX > 0)
			position.x += velocity.x*(gameTime - remainTimeX)*directionX;
		else
		{
			position.x += velocity.x*(gameTime)*directionX;
			collisionXTag = "";
			//Is_BrickCollision = false;
		}
		if (remainTimeY > 0)
			position.y += velocity.y*(gameTime - remainTimeY)*directionY;
		else
		{
			position.y += velocity.y*(gameTime)*directionY;
			collisionYTag = "";
			Is_air = true;
			Is_fall = true;
		}
		if (collisionYTag != "" || collisionXTag != "" || MonsterXTag != "" || MonsterYTag != "")
		{
			UpdateBehavior();
		}
	}
}

void Player::Draw(float gameTime)
{
	if (last_directionX == 1)
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
	if (last_directionX == -1)
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
	Is_BrickCollision = false;
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
		if (Is_BrickCollision == false)
		{
			directionX = -1;
			last_directionX = directionX;
		}
	}break;
	case RIGHT_ARROW:
	{
		if (Is_BrickCollision == false)
		{
			directionX = 1;
			last_directionX = directionX;
		}
	}break;
	case UP_ARROW:
	{
		if (Is_ground_spin == true)
		{
			Is_ground_spin = false;
			position.y = position.y - 40;
			spriteWidth = 14;
			spriteHeight = 20;
			_collisionManager->UpdatePlayerCol(position.x, position.y, spriteWidth, spriteHeight, velocity.x*directionX, velocity.y);
		}
	}break;
	case DOWN_ARROW:
	{
		if (Is_ground_spin != true)
		{
			Is_ground_spin = true;
			position.y = position.y + 10;
			spriteWidth = 13;
			spriteHeight = 13;
			Is_jump = false;
			Is_air = false;
			_collisionManager->UpdatePlayerCol(position.x, position.y, spriteWidth, spriteHeight, velocity.x*directionX, velocity.y);
		}
	}break;

	case SPACE_BUTTON:
	{
		if (Is_jump == false || directionY > 1|| Is_air==false)
		{
			//height_limited = position.y - 50;
			directionY = -1.75;
			Is_jump = true;
			Is_air = true;
			Is_stand = false;
			position.y -= 10;
		}
		break;
	}
	case GOD_MODE:
	{
		if (velocity.y <= 0)
			velocity.y = 0.15f;
		else
			velocity.y = 0;
		break;
	}
	case UNKEY:
	{
		directionX = 0;
	}
	default:
	{

	}
	break;
	}
}

void Player::UpdateBehavior()
{
	if (collisionYTag == "brick")
	{
		if (directionY >= 1)
		{
			Is_jump = false;
			Is_air = false;
			Is_stand = true;
			Is_fall = false;
			directionY = 1;
			//position.y -= 5;
		}
		else
		{
			Is_fall = true;
			directionY = 1;
		}
	}
	if (collisionXTag == "brick")
	{
		Is_BrickCollision = true;
		//directionX = 0;
	}
	if (MonsterXTag != "" || MonsterYTag != "")
	{

	}
}

void Player::jump()
{
	if ( Is_jump==true)
	{
		//height_limited = position.y - 50;
		directionY += -0.75;
		Is_jump = true;
		Is_air = true;
		Is_stand = false;
		position.y -= 10;
	}
}