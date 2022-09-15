#pragma once
class Character
{
public:
	GameObject* col;	// ���� ���� ���� �Ļ� Ŭ�������� nullptr�� �ʱ�ȭ
	ObImage*	idle;
	Vector2		idleImgSize;
	Vector2		scaleCoef;
	int			maxHp;
	int			curHp;

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

