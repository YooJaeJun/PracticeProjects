#pragma once

namespace DanmakuEditor
{
	class Main : public Scene
	{
		enum class ClickState
		{
			none,
			keyDown
		};

	private:
		vector<Vector2>		start;
		vector<Vector2>		end;
		vector<ObImage*>	bullets;
		vector<ObLine*>		lines;
		int					curIdx = 0;
		bool				fireFlag = false;
		ClickState			clickState;
		float				timeExitFire = false;

	public:
		virtual void Init() override;
		void InitBullet();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;
	};
}
