#include"Player.h"

Player::Player(float x, float y, float rotation, float speed, float maxSpeed) :
GameObject(x, y, rotation, speed, maxSpeed)
{

}

bool Player::Initialize(LPDIRECT3DDEVICE9 device)
{
	status = ObjectStatus::Active;
	if (!Right_move)
	{
		Right_move = new GameSprite();
		if (!Right_move->initialize(device, FILE, RIGHT_MOVE_X, RIGHT_MOVE_Y, NORMAL_WIDTH, NORMAL_HEIGHT, RUN_COUNT))
		{
			return false;
		}
	}

	if (!Left_move)
	{
		Left_move = new GameSprite();
		if (!Left_move->initialize(device, FILE, LEFT_MOVE_X, LEFT_MOVE_Y, NORMAL_WIDTH, NORMAL_HEIGHT, RUN_COUNT))
		{
			return false;
		}
	}

	if (!Right_jump)
	{
		Right_jump = new GameSprite();
		if (!Right_jump->initialize(device, FILE, RIGHT_JUMP_X, RIGHT_JUMP_Y, NORMAL_WIDTH, NORMAL_HEIGHT, JUMP_COUNT))
		{
			return false;
		}
	}
	if (!Left_jump)
	{
		Left_jump = new GameSprite();
		if (!Left_jump->initialize(device, FILE, LEFT_JUMP_X, LEFT_JUMP_Y, NORMAL_WIDTH, NORMAL_HEIGHT, JUMP_COUNT))
		{
			return false;
		}
	}
	if (!Right_jump_spin)
	{
		Right_jump_spin = new GameSprite();
		if (!Right_jump_spin->initialize(device, FILE, RIGHT_JUMP_SPIN_X, RIGHT_JUMP_SPIN_Y, NORMAL_WIDTH, NORMAL_HEIGHT, JUMP_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Left_jump_spin)
	{
		Left_jump_spin = new GameSprite();
		if (!Left_jump_spin->initialize(device, FILE, LEFT_JUMP_SPIN_X, LEFT_JUMP_SPIN_Y, NORMAL_WIDTH, NORMAL_HEIGHT, JUMP_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Right_ground_spin)
	{
		Right_ground_spin = new GameSprite();
		if (!Right_ground_spin->initialize(device, FILE, RIGHT_GROUND_SPIN_X, RIGHT_GROUND_SPIN_Y, NORMAL_WIDTH, NORMAL_HEIGHT, GROUND_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Left_ground_spin)
	{
		Left_ground_spin = new GameSprite();
		if (!Left_ground_spin->initialize(device, FILE, LEFT_GROUND_SPIN_X, LEFT_GROUND_SPIN_Y, NORMAL_WIDTH, NORMAL_HEIGHT, GROUND_SPIN_COUNT))
		{
			return false;
		}
	}
	if (!Right_stand)
	{
		Right_stand = new GameSprite();
		if (!Right_stand->initialize(device, FILE, RIGHT_STAND_X, RIGHT_STAND_Y, NORMAL_WIDTH, NORMAL_HEIGHT, STAND_COUNT))
		{
			return false;
		}
	}

	if (!Left_stand)
	{
		Left_stand = new GameSprite();
		if (!Left_stand->initialize(device, FILE, LEFT_STAND_X, LEFT_STAND_Y, NORMAL_WIDTH, NORMAL_HEIGHT, STAND_COUNT))
		{
			return false;
		}
	}

	Is_initialzed = true;

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

		position.x += velocity.x*(gameTime)*direction;
		position.y += velocity.y*(gameTime);
		position.z = 0;
		if (last_direction == 1)
		{
			if (Is_jump == true)
				Right_jump->Update(gameTime);
			else if (Is_fall == true && direction != 0)
				Right_jump_spin->Update(gameTime);
			else if (Is_ground_spin == true)
				Right_ground_spin->Update(gameTime);
			else if (direction != 0)
				Right_move->Update(gameTime);
			else if (Is_stand == true)
				Right_stand->Update(gameTime);
		}
		if (last_direction == -1)
		{
			if (Is_jump == true)
				Left_jump->Update(gameTime);
			else if (Is_fall == true && direction != 0)
				Left_jump_spin->Update(gameTime);
			else if (Is_ground_spin == true)
				Left_ground_spin->Update(gameTime);
			else if (direction != 0)
				Left_move->Update(gameTime);
			else if (Is_stand == true)
				Left_stand->Update(gameTime);
		}
	}

	//Right_move->Update(gameTime);
}

void Player::Draw(float gameTime)
{
	if (last_direction == 1)
	{
		if (Is_jump == true)
			Right_jump->Draw(gameTime, position);
		else if (Is_fall == true && direction != 0)
			Right_jump_spin->Draw(gameTime, position);
		else if (Is_ground_spin == true)
			Right_ground_spin->Draw(gameTime, position);
		else if (direction != 0)
			Right_move->Draw(gameTime, position);
		else if (Is_stand == true)
			Right_stand->Draw(gameTime, position);
	}
	if (last_direction == -1)
	{
		if (Is_jump == true)
			Left_jump->Draw(gameTime, position);
		else if (Is_fall == true && direction != 0)
			Left_jump_spin->Draw(gameTime, position);
		else if (Is_ground_spin == true)
			Left_ground_spin->Draw(gameTime, position);
		else if (direction != 0)
			Left_move->Draw(gameTime, position);
		else if (Is_stand == true)
			Left_stand->Draw(gameTime, position);
	}
	//Right_move->Draw(gameTime, position);
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
		Is_ground_spin = false;
	}break;
	case DOWN_ARROW:
	{
		Is_ground_spin = true;
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