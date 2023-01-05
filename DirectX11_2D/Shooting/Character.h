#pragma once
class Character
{
public:
	GameObject* col;	// 쓰고 싶지 않은 파생 클래스에선 nullptr로 초기화
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

