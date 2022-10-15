#pragma once

namespace Gungeon
{
	enum class State
	{
		idle,
		walk,
		roll,
		attack,
		die
	};

	class Character
	{
	public:
		Character();
		virtual void Init();
		virtual void Release();
		virtual void Update();
		virtual void Update(const bool notRotation);
		virtual void LateUpdate();
		virtual void Render();
		virtual void ResizeScreen();

		inline Int2 On() { return on; }
		inline Vector2 Pos() const { return col->GetWorldPos(); }
		inline void SetPos(const Vector2 pos) { col->SetWorldPos(pos); }
		inline void SetPosX(const float x) { col->SetWorldPosX(x); }
		inline void SetPosY(const float y) { col->SetWorldPosY(y); }
		virtual void Spawn(const Vector2 wpos);
		virtual void ColToggle();

	public:
		GameObject*		col;
		ObRect*			colTile;
		State			state;
		Vector2			moveDir;
		float			scalar;
		int				curHp;
		int				maxHp;
		bool			isHit;

	private:
		Int2			on;
	};
}