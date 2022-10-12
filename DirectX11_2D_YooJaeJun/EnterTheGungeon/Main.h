#pragma once

namespace Gungeon
{
	class Main : public Scene
	{
	private:
		ProcedureMapGeneration* mapGen;
		Player*					player;

	public:
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;
	};
}