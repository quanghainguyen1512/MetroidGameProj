#include"Camera.h"
#include"GraphicDevice.h"

Camera::Camera(int wight, int height, float angle, DirectX::XMFLOAT3 scaleFactor, CollisionManager* collisionManager)
{
	_width = wight;
	_height = height;
	_angle = angle;
	_scaleFactor = scaleFactor;
	_collisionManager = collisionManager;

	D3DXMatrixOrthoLH(&_orthographicMatrix, _width, -_height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&_identifyMatrix);

	status = 1;
	refresh = true;

	limitX = 0;
	limitY = 3136;
	limitWidth = 1280;
	limitHeight = 240;

	limitUp = limitY;
	limitDown = limitY + limitHeight;
	limitRight = limitX + limitWidth;
	limitLeft = limitX;

	stayY = 3256;
}

Camera::~Camera()
{

}

void Camera::Update(bool &autoRun)
{
	cameraX = _width / 2;
	cameraY = _height / 2;
	if (_following&&_following->InitializeFlag())
	{
		cameraX = _following->GetPosition().x;
		cameraY = _following->GetPosition().y;
	}

	if (cameraX + _width / 2 > limitRight)
	{
		cameraX = limitRight - _width / 2;
	}
	if (cameraX - _width / 2 < limitLeft)
	{
		cameraX = limitLeft + _width / 2;
	}
	if (cameraY + _height / 2 > limitDown)
	{
		cameraY = limitDown - _height / 2 + 32;
	}
	if (cameraY - _height / 2 < limitUp)
	{
		cameraY = limitUp + _height / 2 - 32;
	}

	if (_following->Auto == false)
	{
		if (status == 1)
		{
			_viewMatrix = D3DXMATRIX(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				-cameraX, -stayY, 0, 1
				);
			_x = cameraX;
			_y = stayY;
		}
		else if (status == 2)
		{
			_viewMatrix = D3DXMATRIX(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				-stayX, -cameraY, 0, 1
				);
			_x = stayX;
			_y = cameraY;
		}
	}
	else if (_following->Cross == false)
	{
		if (_following->getDirectionX() == 1)
		{
			Transport(autoRun, 1);
		}
		if (_following->getDirectionX() == -1)
		{
			Transport(autoRun, -1);
		}
	}
	else
	{
		if ((_following->GetPosition().x >= limitRight + 32 && _following->getDirectionX() == 1) ||
			(_following->GetPosition().x <= limitLeft - 32 && _following->getDirectionX() == -1))
		{
			_following->terminalAuto();

			FieldCollision* f = _collisionManager->getFieldCollision(_x, _y, _width, _height);
			limitX = f->getX();
			limitY = f->getY();
			limitWidth = f->getWidth();
			limitHeight = f->getHeight();

			int modeF = f->getmode();

			limitUp = limitY;
			limitDown = limitY + limitHeight;
			limitRight = limitX + limitWidth;
			limitLeft = limitX;

			if (modeF == 1)
			{
				status = 1;
				stayY = limitY + limitHeight / 2;
				_y = stayY;
				_x = _following->GetPosition().x;
				if (_x > limitRight)
					_x = limitRight;
				else if (_x < limitLeft)
					_x = limitLeft;

				int cameraX = _x;
				int cameraY = _y;
			}
			else if (modeF == 2)
			{
				status = 2;
				stayX = limitX + limitWidth / 2;
				_x = limitX + limitWidth / 2;
				_y = limitY + limitHeight / 2;
			}
		}
	}
}

void Camera::Follow(Player* following)
{
	
	_following = following;
	_x = following->GetPosition().x;
	_y = following->GetPosition().y;
}

void Camera::Unfollow()
{
	_following = nullptr;
}

bool Camera::IsFollowing() const
{
	return _following != nullptr;
}

void Camera::SetTransform(GraphicsDevice* gDevice) const
{
	gDevice->device->SetTransform(D3DTS_PROJECTION, &_orthographicMatrix);
	gDevice->device->SetTransform(D3DTS_WORLD, &_identifyMatrix);
	gDevice->device->SetTransform(D3DTS_VIEW, &_viewMatrix);
}

bool Camera::changeStatus(int index)
{
	if (_collisionManager->getDoor(index)->getMode() == 1&&
		_collisionManager->getDoor(index)->GetThrough==true&&
		_collisionManager->getDoor(index)->Active == true)
	{
		if (status == 1)
			status = 2;
		else
			status = 1;
		
		limitX = _collisionManager->getDoor(index)->getX() + _collisionManager->getDoor(index)->getWidth() / 2;
		_collisionManager->getDoor(index)->setActive(false);
		playerX = _following->GetPosition().x;
		playerY = _following->GetPosition().y - 48;

		stayX = _following->GetPosition().x;
		stayY = _following->GetPosition().y;

		return true;
	}
	return false;
}

void Camera::Transport(bool &playerAuto, int direction)
{
	if (_x - _width / 2 < limitRight&&_following->getDirectionX() == 1)
	{
		_x = _x + 5;
		direction = 1;
		_following->setDirection(direction);
		if (_x - _width / 2 > limitRight)
			_x = limitRight + _width / 2;
		AutoUpdate();
	}

	else if (_x + _width / 2 > limitLeft&&_following->getDirectionX() == -1)
	{
		_x = _x - 5;
		direction = -1;
		_following->setDirection(direction);
		if (_x + _width / 2 < limitLeft)
			_x = limitLeft - _width / 2;
		AutoUpdate();
	}

	if (_x == limitRight + _width / 2 || _x == limitLeft - _width / 2)
	{
		_following->Cross = true;
	}
}

void Camera::AutoUpdate()
{
	int cameraX = _width / 2;
	int cameraY = _height / 2;
	{
		_viewMatrix = D3DXMATRIX(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			-_x, -_y, 0, 1
			);
	}


}

int Camera::getX()
{
	return _x;
}
int Camera::getY()
{
	return _y;
}
