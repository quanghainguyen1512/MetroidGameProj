#ifndef CAMERA_H
#define CAMERA_H

#include <DirectXMath.h>
#include "Player.h"

class GraphicsDevice;

class Camera
{
public:
	Camera(int wight, int height, float angle, DirectX::XMFLOAT3 scaleFactor);
	~Camera();

	void Update();
	void Follow(Player* following);
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform(GraphicsDevice* gDevice) const;

	int getWidth(){ return _width; }
	int getHeight(){ return _height; }

private:
	float _angle;
	DirectX::XMFLOAT3 _scaleFactor;
	D3DXMATRIX _orthographicMatrix;
	D3DXMATRIX _identifyMatrix;
	D3DXMATRIX _viewMatrix;

	Player* _following;

	int _width;
	int _height;
};

#endif