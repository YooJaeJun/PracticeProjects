#pragma once

namespace Gungeon
{
	class Scene03 : public Scene
	{
	public:
		Scene03();
		~Scene03();

		virtual void Init() override;
		void InitRoom();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;
		void IntersectPlayer();
		void IntersectBoss();
		void ChangeUpdateScene();
		void ColToggle();

	public:
		bool		isChangingScene = false;
		float		timeFade = 0.0f;
		Room*		curRoom = nullptr;
		Player*		player = nullptr;
		Boss*		boss = nullptr;
		Cinematic*	cinematic = nullptr;
	};
}