#pragma once

namespace Dir8
{
	class Scene01 : public Scene
	{
	public:
		Player* pl;
		Boss*	boss;

	public:
		Scene01();
		~Scene01();

		virtual void Init() override;
		virtual void Release() override; //����
		virtual void Update() override;
		virtual void LateUpdate() override;//����
		virtual void Render() override;
		virtual void ResizeScreen() override;
	};
}