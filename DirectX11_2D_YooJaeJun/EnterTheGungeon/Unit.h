#pragma once

namespace Gungeon
{
	enum DirState
	{
		dirB,
		dirL,
		dirR,
		dirLB,
		dirRB,
		dirT,
		dirLT,
		dirRT
	};

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

		virtual void Idle();
		virtual void Hit(const int damage);
		virtual void Die();
		virtual void StartDie();
		void SetLastPosAndDir();
		void StepBack();
		void SetMoveDirState();
		void SetTargetDirState();

	public:
		ObImage*		idle[8];
		ObImage*		walk[8];
		ObImage*		kick[8];
		ObImage*		hit;
		ObImage*		fall;
		ObImage*		die;
		Weapon*			weapon;
		ObImage*		shadow;
		Vector2			lastPos;
		DirState		curMoveDirState;
		DirState		curMoveDirStateBefore;
		DirState		curTargetDirState;
		DirState		curTargetDirStateBefore;
		Vector2			targetPos;
		Vector2			targetDir;
		Vector2			targetDirBefore;
		float			targetRotation;
		float			timeFire;
		float			timeReload;
		float			timeHit;
		bool			isHit;
		bool			isHitAnim;
		float			timeHitAnim;
		float			timeDieAnim;
		ObRect*			foot;
		float			timeRealDie;
	};
}