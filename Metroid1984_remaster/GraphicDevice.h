#ifndef GRAPHICDEVICE_H
#define GRAPHICDEVICE_H 

#include<d3d9.h>

class  GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	bool Initialize(HWND hWnd, bool windowed);
	void Clear(D3DCOLOR color);
	void Begin();
	void End();
	void Present();
	LPDIRECT3DDEVICE9 device;
private:
	LPDIRECT3D9 direct3d;

};


#endif