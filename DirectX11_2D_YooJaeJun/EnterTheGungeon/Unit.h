#pragma once

namespace Gungeon
{
	class Unit : public Character
	{
	public:
		Unit();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;

		virtual void SetTarget(Weapon*& weapon);
		virtual void Idle();
		virtual void Walk();
		virtual void Hit(const int damage);
		virtual void Die();
		void StartWalk();
		void StartIdle();
		virtual void StartDie();
		virtual void Spawn(const Vector2 wpos) override;
		void SetLastPosAndDir();
		void StepBack();
		void SetDirState(const Vector2 dir, DirState& dirState);
		void FindPath(ObTileMap* map);
		void DontFindPath();

	public:
		ObImage*			spawn;
		ObImage*			idle;
		ObImage*			walk;
		ObImage*			kick;
		ObImage*			hit;
		ObImage*			fall;
		ObImage*			die;
		ObImage*			shadow;
		Item*				dropItem;
		vector<Bullet*>		bullet;
		Vector2				lastPos;
		DirState			curMoveDirState;
		DirState			curMoveDirStateBefore;
		DirState			curTargetDirState;
		DirState			curTargetDirStateBefore;
		Vector2				targetPos;
		Vector2				targetDir;
		Vector2				targetDirBefore;
		Vector2				originCamPos;
		float				timeFire;
		float				timeReload;
		Vector2				pushedDir;
		float				timeHit;
		bool				isHit;
		bool				isHitAnim;
		float				timeHitAnim;
		float				timeDieAnim;
		float				timeRealDie;
		vector<Tile*>		way;
		Vector2				start;
		Vector2				end;
		float				g;	// ∫Ò¿≤
		float				timeFindPath;
	};
}