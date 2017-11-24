#include"Camera.h"
#include"GraphicDevice.h"

Camera::Camera(int wight, int height, float angle, DirectX::XMFLOAT3 scaleFactor)
{
	_width = wight;
	_height = height;
	_angle = angle;
	_scaleFactor = scaleFactor;

	D3DXMatrixOrthoLH(&_orthographicMatrix, _width, -_height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&_identifyMatrix);

}

Camera::~Camera()
{

}

void Camera::Update()
{
	int cameraX = _width / 2;
	int cameraY = _height / 2;
	if (_following&&_following->InitializeFlag())
	{
		cameraX = _following->GetPosition().x;
		cameraY = _following->GetPosition().y - 32;
	}

	_viewMatrix = D3DXMATRIX(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-cameraX, -cameraY, 0, 1
		);
}

void Camera::Follow(Player* following)
{
	_following = following;
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
