#pragma once
class Character
{
public:
	GameObject* col;	// ���� ���� ���� �Ļ� Ŭ�������� nullptr�� �ʱ�ȭ
	ObImage*	idle;
	Vector2		imgSize;
	float		scaleCoefX;
	float		scaleCoefY;

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

