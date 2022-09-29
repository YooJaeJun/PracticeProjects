#include "stdafx.h"

namespace Dir8
{
	Character::Character()
	{
		moveDir = Vector2(0.0f, 0.0f);
		scalar = 100.0f;
		state = CharacterState::IDLE;
	}

	void Character::LookTarget()
	{
		float radian = Utility::DirToRadian(targetDir);

		if (radian < DIV8PI && radian > -DIV8PI)
		{
			targetDirstate = DIR_R;
		}
		else if (radian > DIV8PI && radian < DIV8PI + DIV4PI)
		{
			targetDirstate = DIR_RT;
		}
		else if (radian > DIV8PI + DIV4PI && radian < DIV8PI + DIV4PI * 2.0f)
		{
			targetDirstate = DIR_T;
		}
		else if (radian > DIV8PI + DIV4PI * 2.0f && radian < DIV4PI * 3.0f + DIV8PI)
		{
			targetDirstate = DIR_LT;
		}
		else if (radian > -(DIV8PI + DIV4PI * 3.0f) && radian < -(DIV4PI * 2.0f + DIV8PI))
		{
			targetDirstate = DIR_LB;
		}
		else if (radian > -(DIV8PI + DIV4PI * 2.0f) && radian < -(DIV4PI + DIV8PI))
		{
			targetDirstate = DIR_B;
		}
		else if (radian > -(DIV8PI + DIV4PI) && radian < -DIV8PI)
		{
			targetDirstate = DIR_RB;
		}
		else
		{
			targetDirstate = DIR_L;
		}
	}
}