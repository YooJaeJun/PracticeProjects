#pragma once

class Character
{
public:
	Character();

	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

	inline Vector2 Pos() const { return col->GetWorldPos(); }
	inline void SetPos(const Vector2 pos) { col->SetWorldPos(pos); }
	inline void SetPosX(const float x) { col->SetWorldPosX(x); }
	inline void SetPosY(const float y) { col->SetWorldPosY(y); }

public:
	GameObject*		col;
	Vector2			moveDir;
	float			scalar;
	int				curHp;
	int				maxHp;
	bool			isHit;
};

