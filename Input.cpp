#include "framework.h"

Input::Input()
{
	// ���� �ּҺ��� ������ �޸� 0���� �ʱ�ȭ
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}

Input::~Input()
{
}

bool Input::KeyDown(int KeyCode)
{
	return keyMap[KeyCode] == KEY_INPUT_STATUS_DOWN;
}

bool Input::KeyPress(int KeyCode)
{
	return keyMap[KeyCode] <= KEY_INPUT_STATUS_PRESS;	// <= down �� ����
}

bool Input::KeyUp(int KeyCode)
{
	return keyMap[KeyCode] <= KEY_INPUT_STATUS_UP;
}

void Input::Update()
{
	// �޸� ���� keyOldState = keyState
	//				dest		src
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	// ������ �迭�� �ʱ�ȭ
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	// ���� ȣ����¿����� Ű�Է°��� �������� �Լ�
	if (GetKeyboardState(keyState))
	{
		for (UINT i = 0; i < 256; i++)
		{
			byte key = keyState[i] & 0x80;
			// ���׿�����
			keyState[i] = key ? 1 : 0;

			int oldState = keyOldState[i];
			int state = keyState[i];

			if (oldState == 0 && state == 1)
				keyMap[i] = KEY_INPUT_STATUS_DOWN;	// ���� 0, ���� 1 - KeyDown
			if (oldState == 1 && state == 0)
				keyMap[i] = KEY_INPUT_STATUS_UP;	// ���� 1, ���� 0 - KeyUp
			if (oldState == 1 && state == 1)
				keyMap[i] = KEY_INPUT_STATUS_PRESS;	// ���� 1, ���� 1 - KeyPress
			else
				keyMap[i] = KEY_INPUT_STATUS_NONE;
		}
	}
	// 0x80    1000  0000  �������ȴ����� ���� ����
	// 0x81    1000  0001  �������������� ���� ����
	// 0x00    0000  0000
	// 0x01    0000  0001

	//&

	// 0x80    1000  0000
}
