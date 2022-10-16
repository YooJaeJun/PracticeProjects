#pragma once

namespace Gungeon
{
	enum class UIType
	{
		none,
		prop,
		gauge,
		font
	};

	enum class Anchor
	{
		none,
		leftTop,
		leftBottom,
		rightBottom
	};

	class UI
	{
	public:
		UI();

		void Release();
		void Update();
		void LateUpdate();
		void Render();

		void Spawn(const float xFactor, const float yFactor);
		bool DownGauge();

	public:
		ObImage*	img = nullptr;
		Anchor		anchor = Anchor::none;
		Vector2		imgSize;
	};
}
