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

		void Spawn(const float coefX, const float coefY);
		bool DownGauge();

	public:
		ObImage*	img;
		Anchor		anchor;
		Vector2		imgSize;
	};
}
