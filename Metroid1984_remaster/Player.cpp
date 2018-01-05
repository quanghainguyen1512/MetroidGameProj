#include"Player.h"

Player::Player(float x, float y, float rotation, float speed, float maxSpeed, CollisionManager* collisionManager, SpriteManager* spritemanager, GraphicsDevice* gDevice) :
GameObject(x, y, rotation, speed, maxSpeed, collisionManager, spritemanager, gDevice)
{
	velocity.y = 0.15f;
	bulletCount = 5;
	shootable = true;
	bulletIndex = 0;
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

	if (!Right_look_up)
	{
		Right_look_up = new GameSprite(_spriteManager);
		if (!Right_look_up->initialize(device, _gDevice->getCharaterTex(), RIGHT_STAND_GAURD_INDEX, STAND_GAURD_COUNT))
		{
			return false;
		}
	}
	if (!Left_look_up)
	{
		Left_look_up = new GameSprite(_spriteManager);
		if (!Left_look_up->initialize(device, _gDevice->getCharaterTex(), LEFT_STAND_GAURD_INDEX, STAND_GAURD_COUNT))
		{
			return false;
		}
	}
	if (!Right_move_look)
	{
		Right_move_look = new GameSprite(_spriteManager);
		if (!Right_move_look->initialize(device, _gDevice->getCharaterTex(), RIGHT_MOVE_GAURD_INDEX, MOVE_GAURD_COUNT))
		{
			return false;
		}
	}
	if (!Left_move_look)
	{
		Left_move_look = new GameSprite(_spriteManager);
		if (!Left_move_look->initialize(device, _gDevice->getCharaterTex(), LEFT_MOVE_GAURD_INDEX, MOVE_GAURD_COUNT))
		{
			return false;
		}

	}
	if (!Right_jump_look)
	{
		Right_jump_look = new GameSprite(_spriteManager);
		if (!Right_jump_look->initialize(device, _gDevice->getCharaterTex(), RIGHT_JUMP_GAURD_INDEX, JUMP_GAURD_COUNT))
		{
			return false;
		}
	}
	if (!Left_jump_look)
	{
		Left_jump_look = new GameSprite(_spriteManager);
		if (!Left_jump_look->initialize(device, _gDevice->getCharaterTex(), LEFT_JUMP_GAURD_INDEX, JUMP_GAURD_COUNT))
		{
			return false;
		}
	}
	if (!Right_move_shoot)
	{
		Right_move_shoot = new GameSprite(_spriteManager);
		if (!Right_move_shoot->initialize(device, _gDevice->getCharaterTex(), RIGHT_MOVE_SHOOT_INDEX, MOVE_SHOOT_COUNT))
		{
			return false;
		}
	}
	if (!Left_move_shoot)
	{
		Left_move_shoot = new GameSprite(_spriteManager);
		if (!Left_move_shoot->initialize(device, _gDevice->getCharaterTex(), LEFT_MOVE_SHOOT_INDEX, MOVE_SHOOT_COUNT))
		{
			return false;
		}
	}

	if (CreateBullet() == false)
		return false;

	Is_initialzed = true;
	spriteID = 4; 
	ActionID = 2;

	spriteWidth = Right_stand->getWidth();
	spriteHeight = Right_stand->getHeight();

	collisionXTag = "";
	collisionYTag = "";
	MonsterXTag = 0;
	MonsterYTag = 0;

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
			if (HighJump == true)
			{
				hightjumpcount++;
				if (hightjumpcount == 2)
					directionY -= 2.0;
			}
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
				if (Is_jumpgaurd == false)
				{
					Right_jump->Update(gameTime);
					spriteID = 0;
					ActionID = 2;
					spriteWidth = Right_jump->getWidth();
					spriteHeight = Right_jump->getHeight();
					shootable = true;
				}
				else
				{
					Right_jump_look->Update(gameTime);
					spriteID = 5;
					spriteWidth = Right_jump_look->getWidth();
					spriteHeight = Right_jump_look->getHeight();
					shootable = true;
				}
				//Is_air = true;
			}
			else if (Is_fall == true && directionX != 0 && Is_air == true && directionY > 0)
			{
				Right_jump_spin->Update(gameTime);
				spriteID = 1;
				ActionID = 2;
				spriteWidth = Right_jump_spin->getWidth();
				spriteHeight = Right_jump_spin->getHeight();
				shootable = false;
				//Is_air = true;
			}
			else if (Is_ground_spin == true)
			{
				Right_ground_spin->Update(gameTime);
				spriteID = 2;
				ActionID = 0;
				spriteWidth = Right_ground_spin->getWidth();
				spriteHeight = Right_ground_spin->getHeight();
				shootable = false;
			}
			else if (directionX != 0 && Is_air == false)
			{
				if (Is_movegaurd == false)
				{
					if (OpenFire == false)
					{
						Right_move->Update(gameTime);
						spriteID = 3;
						ActionID = 0;
						spriteWidth = Right_move->getWidth();
						spriteHeight = Right_move->getHeight();
						shootable = true;
					}
					else
					{
						Right_move_shoot->Update(gameTime);
						spriteID = 8;
						spriteWidth = Right_move_shoot->getWidth();
						spriteHeight = Right_move_shoot->getHeight();
						shootable = true;
					}
				}
				else
				{
					Right_move_look->Update(gameTime);
					spriteID = 7;
					spriteWidth = Right_move_look->getWidth();
					spriteHeight = Right_move_look->getHeight();
					shootable = true;
				}
			}
			else if (Is_stand == true)
			{
				if (Is_standgaurd == false)
				{
					Right_stand->Update(gameTime);
					spriteID = 4;
					ActionID = 3;
					spriteWidth = Right_stand->getWidth();
					spriteHeight = Right_stand->getHeight();
					shootable = true;
				}
				else
				{
					Right_look_up->Update(gameTime);
					spriteID = 6;
					spriteWidth = Right_look_up->getWidth();
					spriteHeight = Right_look_up->getHeight();
					shootable = true;
				}
			}
		}
		if (last_directionX == -1)
		{
			if ((Is_jump == true || Is_air == true) && Is_ground_spin == false && (directionX == 0))
			{
				if (Is_jumpgaurd == false)
				{
					Left_jump->Update(gameTime);
					spriteID = 0;
					ActionID = 2;
					spriteWidth = Left_jump->getWidth();
					spriteHeight = Left_jump->getHeight();
					shootable = true;
				}
				else
				{
					Left_jump_look->Update(gameTime);
					spriteID = 5;
					spriteWidth = Left_jump_look->getWidth();
					spriteHeight = Left_jump_look->getHeight();
					shootable = true;
				}
				//Is_air = true;
			}
			else if (Is_fall == true && directionX != 0 && Is_air == true && directionY > 0)
			{
				Left_jump_spin->Update(gameTime);
				spriteID = 1;
				ActionID = 2;
				spriteWidth = Left_jump_spin->getWidth();
				spriteHeight = Left_jump_spin->getHeight();
				shootable = false;
				//Is_air = true;
			}
			else if (Is_ground_spin == true)
			{
				Left_ground_spin->Update(gameTime);
				spriteID = 2;
				ActionID = 1;
				spriteWidth = Left_ground_spin->getWidth();
				spriteHeight = Left_ground_spin->getHeight();
				shootable = false;
			}
			else if (directionX != 0 && Is_air == false)
			{
				if (Is_movegaurd == false)
				{
					if (OpenFire == false)
					{
						Left_move->Update(gameTime);
						spriteID = 3;
						ActionID = 1;
						spriteWidth = Left_move->getWidth();
						spriteHeight = Left_move->getHeight();
						shootable = true;
					}
					else
					{
						Left_move_shoot->Update(gameTime);
						spriteID = 8;
						spriteWidth = Left_move_shoot->getWidth();
						spriteHeight = Left_move_shoot->getHeight();
						shootable = true;
					}
				}
				else
				{
					Left_move_look->Update(gameTime);
					spriteID = 7;
					spriteWidth = Left_move_look->getWidth();
					spriteHeight = Left_move_look->getHeight();
					shootable = true;
				}
			}
			else if (Is_stand == true)
			{
				if (Is_standgaurd == false)
				{
					Left_stand->Update(gameTime);
					spriteID = 4;
					ActionID = 3;
					spriteWidth = Left_stand->getWidth();
					spriteHeight = Left_stand->getHeight();
					shootable = true;
				}
				else
				{
					Left_look_up->Update(gameTime);
					spriteID = 6;
					spriteWidth = Left_look_up->getWidth();
					spriteHeight = Left_look_up->getHeight();
					shootable = true;
				}
			}
		}

		if (Auto == false)
		{
			_collisionManager->UpdatePlayerCol(tempx, tempy, spriteWidth, spriteHeight, velocity.x*directionX, velocity.y*directionY);
			_collisionManager->BulletProcess();
			float remainTimeX = _collisionManager->RemainXtime(position.x, lastWidth, velocity.x*directionX, collisionXTag, MonsterXTag);
			float remainTimeY = _collisionManager->RemainYtime(position.y, lastHeight, velocity.y*directionY, collisionYTag, MonsterYTag);
			
			//if (collisionXTag == "door")
			if (collisionYTag != "" || collisionXTag != "" || MonsterXTag != 0 || MonsterYTag != 0)
				UpdateBehavior();
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
			if (collisionYTag != "" || collisionXTag != "" || MonsterXTag != 0 || MonsterYTag != 0)
			{
				if (collisionXTag == "door")
					UpdateBehavior();

				UpdateBehavior();
			}

			BulletControl(gameTime);
		}
		else if (Cross==true)
		{
			if (last_directionX == -1)
			{
				position.x += velocity.x*(gameTime)*last_directionX;
			}
			position.x += velocity.x*(gameTime)*last_directionX;
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
		case 5:
		{
			Right_jump_look->Draw(gameTime, position);
			break;
		}
		case 6:
		{
			Right_look_up->Draw(gameTime, position);
			break;
		}
		case 7:
		{
			Right_move_look->Draw(gameTime, position);
			break;
		}
		case 8:
		{
			Right_move_shoot->Draw(gameTime, position);
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
		case 5:
		{
			Left_jump_look->Draw(gameTime, position);
			break;
		}
		case 6:
		{
			Left_look_up->Draw(gameTime, position);
			break;
		}
		case 7:
		{
			Left_move_look->Draw(gameTime, position);
			break;
		}
		case 8:
		{
			Left_move_shoot->Draw(gameTime, position);
			break;
		}
		default:
			break;
		}
	}

	DrawBullet();

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
	if (Auto == false)
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
			shootUP = true;
			if (Is_ground_spin == true)
			{
				Is_ground_spin = false;
				position.y = position.y - 40;
				spriteWidth = 14;
				spriteHeight = 20;
				_collisionManager->UpdatePlayerCol(position.x, position.y, spriteWidth, spriteHeight, velocity.x*directionX, velocity.y);
			}
			else if (Is_jump == true && Is_air == true && Is_stand == false)
			{
				Is_jumpgaurd = true;
			}
			else if (directionX == 0)
			{
				Is_standgaurd = true;
			}
		}break;
		case DOWN_ARROW:
		{
			if (Is_ground_spin != true && !(Is_jump == true && Is_air == true && Is_stand == false))
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

		case JUMP_BUTTON:
		{
			if (((Is_jump == false || directionY > 1 || Is_air == false) && Is_ground_spin == false) && jumpCount == 0)
			{
				//height_limited = position.y - 50;
				directionY = -0.25;
				Is_jump = true;
				Is_air = true;
				Is_stand = false;
				position.y -= 5;
				jumpCount++;
			}
			break;
		}
		/*case SHOOT_BUTTON:
		{
		break;
		}*/
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
			countDown = 5;
			timeShot = 0;
			Is_jumpgaurd = false;
			Is_standgaurd = false;
			Is_movegaurd = false;
			shootUP = false;
			Is_moveshoot = false;
			jumpCount = 0;
			HighJump = false;
			hightjumpcount = 0;
		}
		default:
		{

		}
		break;
		}
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
			Did_jump = false;
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
		directionX = 0;
		spriteID = 4;
	}
	else if (collisionXTag == "door")
	{
		Auto = true;
		spriteID = 4;
	}
	if (MonsterXTag == 1 || MonsterYTag == 1)
	{
		position.x -= 5;
	}
	else if (MonsterXTag==2||MonsterYTag==2)
	{
		position.x += 5;
	}
	MonsterXTag = 0;
	MonsterYTag = 0;
}

void Player::jump()
{
	HighJump = true;
}

bool Player::CreateBullet()
{
	for (int i = 0; i < bulletCount; i++)
	{
		Bullet* b = new Bullet(position.x, position.y, _rotation, _speed, _MaxSpeed, _collisionManager, _spriteManager, _gDevice);
		if (b->Initialize(_gDevice->device) == false)
			return false;
		bulletList.push_back(b);
		_collisionManager->ImportBulletCollision(i, position.x, position.y, 8, 8);
	}
	return true;
}

void Player::Shoot()
{
	if (shootable == true)
	{
		if (timeShot == 0)
		{
			if (shootUP == false)
			{
				bulletList[bulletIndex]->SetVector(last_directionX, 0, velocity.x, velocity.y);
			}
			else
			{
				bulletList[bulletIndex]->SetVector(0, -1, velocity.x, velocity.y);
			}
			if (last_directionX == 1)
			{
				bulletList[bulletIndex]->UpdatePosition(position.x + spriteWidth - 5, position.y + 8);
			}
			else if (last_directionX == -1)
			{
				bulletList[bulletIndex]->UpdatePosition(position.x, position.y + 8);
			}
			bulletList[bulletIndex]->Update(0);
			bulletList[bulletIndex]->active = true;
			_collisionManager->UpdateBulletCol(bulletIndex, bulletList[bulletIndex]->getPosition().x, bulletList[bulletIndex]->getPosition().y, 0, 0, true);
			bulletIndex++;
			if (bulletIndex > 4)
				bulletIndex = 0;
		}
		timeShot++;
		if (timeShot >= countDown)
		{
			timeShot = 0;	
		}
		
		//moveShoot();
	}
}

void Player::BulletControl(float gameTime)
{
	for (int i = 0; i < bulletCount; i++)
	{
		if (_collisionManager->getBulletActive(i) == true)
		{
			bulletList[i]->Update(gameTime);
			_collisionManager->UpdateBulletCol(i, bulletList[i]->getPosition().x, bulletList[i]->getPosition().y, 0, 0, true);
		}
		else
		{
			bulletList[i]->Reset();
			_collisionManager->UpdateBulletCol(i, bulletList[i]->getPosition().x, bulletList[i]->getPosition().y, 0, 0, false);
		}
	}
	
	if (OpenFire == true)
	{
		Shoot();
	}
	
}

void Player::DrawBullet()
{
	for (int i = 0; i < bulletCount; i++)
	{
		if (bulletList[i]->active == true)
		{
			bulletList[i]->Draw(0);
		}
	}
}

void Player::movegaurd()
{
	//if (directionX != 0)
	{
		shootUP = true;
		Is_movegaurd = true;
		//position.y += 2;
	}
}

void Player::moveGaurdTerminated()
{
	shootUP = false;
	Is_movegaurd = false;
	Is_air = false;
	Is_fall = false;
	//position.y += 9;

}

void Player::resetHighJump()
{
	hightjumpcount = 0;
	HighJump = false;
}

void Player::startShoot()
{
	OpenFire = true;
}
void Player::endShoot()
{
	OpenFire = false;
	timeShot = 0;
}

void Player::setDirection(int direction)
{
	directionX = direction;
}

int Player::getDirectionX()
{
	return last_directionX;
}

void Player::setAuto(bool &_auto, int direction, int limitX, bool &_pause)
{
	Auto = _auto;
	directionX = direction;
	directionY = 0;
	autoLimitX = limitX;
	Is_movegaurd = false;
	Is_air = false;
	
}

void Player::terminalAuto()
{
	Auto = false;
	Cross = false;
	directionX = 0;
	directionY = 1;
}