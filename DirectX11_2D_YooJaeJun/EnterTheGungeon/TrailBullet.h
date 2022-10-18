#pragma once

namespace Gungeon
{
	class TrailBullet : public Bullet
	{
	public:
		TrailBullet();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void Update(const bool notRotation) override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void Reload() override;

	public:
		deque<ObImage*>	trails;
		float			timeTrail;
		float			timeSpawnTrail;
		float			trailDuration;
		int				trailNum;
	};
}