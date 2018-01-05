#ifndef CAMERA_H
#define CAMERA_H

#include <DirectXMath.h>
#include "Player.h"

class GraphicsDevice;

class Camera
{
public:
	Camera(int wight, int height, float angle, DirectX::XMFLOAT3 scaleFactor, CollisionManager* collisionManager);
	~Camera();

	void Update(bool &autoRun);
	void Follow(Player* following);
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform(GraphicsDevice* gDevice) const;

	void Transport( bool &playerAuto, int direction);
	void AutoUpdate();
	bool changeStatus(int index);

	int getWidth(){ return _width; }
	int getHeight(){ return _height; }

	int getX();
	int getY();

private:
	float _angle;
	DirectX::XMFLOAT3 _scaleFactor;
	D3DXMATRIX _orthographicMatrix;
	D3DXMATRIX _identifyMatrix;
	D3DXMATRIX _viewMatrix;

	Player* _following;

	int _width;
	int _height;
	bool refresh;

	CollisionManager* _collisionManager;
	int status;

	int stayX;
	int stayY;

	int limitX;
	int limitY;
	int limitWidth;
	int limitHeight;
	
	int limitUp;
	int limitDown;
	int limitLeft;
	int limitRight;

	int playerX;
	int playerY;

	int _x; int _y;
	int cameraX;
	int cameraY;
	
};

#endif