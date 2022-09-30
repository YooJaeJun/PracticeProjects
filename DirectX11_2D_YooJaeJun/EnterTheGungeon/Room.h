#pragma once

namespace Gungeon
{
	class Room : public Character
	{
	public:
		bool	selected;

	public:
		Room();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}
