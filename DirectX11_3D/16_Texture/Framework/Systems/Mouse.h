#pragma once

#define MAX_INPUT_MOUSE 8

class Mouse
{
public:
	void SetHandle(HWND handle)
	{
		this->handle = handle;
	}

	static Mouse* Get();

	static void Create();
	static void Delete();

	void Update();

	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);

	D3DXVECTOR3 GetPosition() { return position; }

	bool Down(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_DOWN;
	}

	bool Up(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_UP;
	}

	bool Press(DWORD button)
	{
		return buttonMap[button] == BUTTON_INPUT_STATUS_PRESS;
	}

	D3DXVECTOR3 GetMoveValue()
	{
		return wheelMoveValue;
	}

private:
	Mouse();
	~Mouse();

	static Mouse* instance;

	HWND handle;
	D3DXVECTOR3 position; //���콺 ��ġ

	byte buttonStatus[MAX_INPUT_MOUSE];
	byte buttonOldStatus[MAX_INPUT_MOUSE];
	byte buttonMap[MAX_INPUT_MOUSE];

	D3DXVECTOR3 wheelStatus;
	D3DXVECTOR3 wheelOldStatus;
	D3DXVECTOR3 wheelMoveValue;

	DWORD timeDblClk;
	DWORD startDblClk[MAX_INPUT_MOUSE];
	int buttonCount[MAX_INPUT_MOUSE];

	enum
	{
		MOUSE_ROTATION_NONE = 0,
		MOUSE_ROTATION_LEFT,
		MOUSE_ROTATION_RIGHT
	};

	enum
	{
		BUTTON_INPUT_STATUS_NONE = 0,
		BUTTON_INPUT_STATUS_DOWN,
		BUTTON_INPUT_STATUS_UP,
		BUTTON_INPUT_STATUS_PRESS,
		BUTTON_INPUT_STATUS_DBLCLK
	};
};

