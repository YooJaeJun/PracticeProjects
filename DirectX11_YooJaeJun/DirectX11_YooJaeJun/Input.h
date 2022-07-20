#pragma once

class Input : public Singleton<Input>
{
private:
	unsigned char keyState[256];	// �������
	unsigned char keyOldState[256];	// ����������Ʈ����
	unsigned char keyMap[256];

	// �͸� enum		// �������� ȣ������ ����
	enum
	{
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_PRESS,
		KEY_INPUT_STATUS_NONE,
		KEY_INPUT_STATUS_UP,
	};

public:
	Input();
	~Input();

	bool KeyDown(int KeyCode);	// ������ �� ����1ȸ
	bool KeyPress(int KeyCode);	// ������ ���� ��
	bool KeyUp(int KeyCode);	// �����ٰ� ������ �� ����1ȸ
	void Update();
};

