#pragma once

namespace Gungeon
{
	class Main : public Scene
	{
	public:
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;

	private:
		ProcedureMapGeneration* mapGen = nullptr;
		Player* player = nullptr;
	};
}