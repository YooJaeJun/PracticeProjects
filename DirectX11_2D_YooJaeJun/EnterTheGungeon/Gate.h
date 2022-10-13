#pragma once

namespace Gungeon
{
	class Gate : public Obstacle
	{
	public:
		Gate();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}
