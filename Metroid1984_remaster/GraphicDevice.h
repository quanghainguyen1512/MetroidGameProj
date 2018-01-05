#ifndef GRAPHICDEVICE_H
#define GRAPHICDEVICE_H 

#include"DataSet.h"
#include<d3dx9.h>
#include<d3d9.h>
#include<iostream>
#include<string>

using namespace std;

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

	bool CreateCharacterTex(string fileName);
	bool CreateBrickTex(string fileName);

	LPDIRECT3DDEVICE9 device;

	LPDIRECT3DTEXTURE9 getCharaterTex();
	LPDIRECT3DTEXTURE9 getBrickTex();

private:
	LPDIRECT3D9 direct3d;
	LPDIRECT3DTEXTURE9 characterTex;
	LPDIRECT3DTEXTURE9 brickTex; 

};


#endif