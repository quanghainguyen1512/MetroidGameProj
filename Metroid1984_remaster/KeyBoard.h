#ifndef KEYBOARD
#define KEYBOARD

#include<Windows.h>
#include<dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024

class KeyBoard
{
public:
	KeyBoard();
	~KeyBoard();

	bool InitializeKeyBoard(HWND hWnd, HINSTANCE hInstance);
	void ProcessKeyBoard(HWND hWnd);
	int IsKeyDown(int KeyCode);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	//void ProcessInput();

private:
	/*HWND _hWnd;*/

	LPDIRECTINPUT8 _di;
	LPDIRECTINPUTDEVICE8 _keyboard;
	BYTE _keyStates[256];
	DIDEVICEOBJECTDATA _keyEvents[KEYBOARD_BUFFER_SIZE];
};
#endif