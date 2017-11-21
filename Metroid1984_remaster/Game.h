#ifndef GAME_H
#define GAME_H

#include"GraphicDevice.h"
#include<dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024

class Game
{
public:
	Game();
	~Game();

	bool Initialize(HWND hWnd, HINSTANCE hInstance, int width, int height);
	void Run(float gameTime);
	void Update(float gameTime);
	void Draw(float gameTime);

private:
	GraphicsDevice *gDevice;

	int _width;
	int _height;

	float _gameTime;

};

#endif GAME_H