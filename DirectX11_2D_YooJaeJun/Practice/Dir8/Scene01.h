#pragma once

namespace Dir8
{
	class Scene01 : public Scene
	{
	public:
		// Tilemap
		ObTileMap* tilemap;
		int			imgIdx;
		Int2		tileSize;
		Color		tileColor;
		int			tileState;
		Int2		mouseIdx;
		Int2		pickingIdx;
		// game
		Player*		pl;
		Boss*		boss;

	public:
		Scene01();
		~Scene01();

		virtual void Init() override;
		virtual void Release() override; //해제
		virtual void Update() override;
		virtual void LateUpdate() override;//갱신
		virtual void Render() override;
		virtual void ResizeScreen() override;
	};
}