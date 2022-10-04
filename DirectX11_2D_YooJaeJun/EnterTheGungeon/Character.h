#pragma once

namespace Gungeon
{
	enum class State
	{
		idle,
		walk,
		roll,
		die
	};

	class Character
	{
	public:
		Character();
		virtual void Init();
		virtual void Release();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void ResizeScreen();

		inline Vector2 Pos() const { return col->GetWorldPos(); }
		inline void SetPos(const Vector2 pos) { col->SetWorldPos(pos); }
		inline void SetPosX(const float x) { col->SetWorldPosX(x); }
		inline void SetPosY(const float y) { col->SetWorldPosY(y); }
		virtual void Spawn(const Vector2 wpos);

	public:
		GameObject*		col;
		State			state;
		Vector2			moveDir;
		float			scalar;
		int				curHp;
		int				maxHp;
		bool			isHit;
	};
}