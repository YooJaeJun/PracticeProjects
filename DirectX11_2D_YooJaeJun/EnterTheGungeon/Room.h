#pragma once

namespace Gungeon
{
	class Room : public Character
	{
	public:
		Room();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:
		bool		selected;
		Effect*		spawnEffect[4];
	};
}
