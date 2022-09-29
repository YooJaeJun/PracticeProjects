#pragma once

namespace Dir8
{
	class Boss : public Character
	{
	public:
		ObImage* walk;
		ObCircle* rangeAtk;
		ObCircle* rangeTrace;
		ObCircle* rangeLook;

	public:
		Boss();
		~Boss();

		void Release();
		void Update();
		void Render();

		void Idle();
		void Walk();

		void Atk();
		void Trace();
		virtual void LookTarget() override;
	};
}

