#pragma once

class Character
{
public:
	Character();

	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void ResizeScreen();

	inline Vector2 Pos() const { return col->GetWorldPos(); }
	inline void SetPos(const Vector2 pos) { col->SetWorldPos(pos); }
	inline void SetPosX(const float x) { col->SetWorldPosX(x); }
	inline void SetPosY(const float y) { col->SetWorldPosY(y); }
	inline void Spawn(const Vector2 wpos) 
	{
		SetPosX(wpos.x);
		SetPosY(wpos.y);
	}

public:
	GameObject*		col;
	Vector2			moveDir;
	float			scalar;
	int				curHp;
	int				maxHp;
	bool			isHit;
};

