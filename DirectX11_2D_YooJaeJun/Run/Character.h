#pragma once
class Character
{
public:
	GameObject* col;	// ���� ���� ���� �Ļ� Ŭ�������� nullptr�� �ʱ�ȭ
	int			hp;
	float		scaleXCoef;
	float		scaleYCoef;

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

