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
		virtual void Hit(const int damage);
		virtual void Die();
		virtual void StartDie();
		void SetLastPosAndDir();
		void StepBack();
		void SetMoveDirState();
		void SetTargetDirState();
		void FindPath(ObTileMap* map);

	public:
		ObImage*			spawn;
		ObImage*			idle[8];
		ObImage*			walk[8];
		ObImage*			kick[8];
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
		float				targetRotation;
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