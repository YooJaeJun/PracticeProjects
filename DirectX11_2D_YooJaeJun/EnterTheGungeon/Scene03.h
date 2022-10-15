#pragma once

namespace Gungeon
{
	class Scene03 : public Scene
	{
	public:
		bool		isChangingScene;
		float		timeFade;
		Room*		curRoom;
		Player*		player;
		Boss*		boss;

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
	};
}