#include "stdafx.h"

namespace Dir8
{
	void Character::LookTarget(Vector2 target, ObImage* img)
	{
		Vector2 dir = target - col->GetWorldPos();
		float radian = Utility::DirToRadian(dir);

		if (radian < DIV8PI && radian > -DIV8PI)
		{
			dirState = DIR_R;
		}
		else if (radian > DIV8PI && radian < DIV8PI + DIV4PI)
		{
			dirState = DIR_RT;
		}
		else if (radian > DIV8PI + DIV4PI && radian < DIV8PI + DIV4PI * 2.0f)
		{
			dirState = DIR_T;
		}
		else if (radian > DIV8PI + DIV4PI * 2.0f && radian < DIV4PI * 3.0f + DIV8PI)
		{
			dirState = DIR_LT;
		}
		else if (radian > -(DIV8PI + DIV4PI * 3.0f) && radian < -(DIV4PI * 2.0f + DIV8PI))
		{
			dirState = DIR_LB;
		}
		else if (radian > -(DIV8PI + DIV4PI * 2.0f) && radian < -(DIV4PI + DIV8PI))
		{
			dirState = DIR_B;
		}
		else if (radian > -(DIV8PI + DIV4PI) && radian < -DIV8PI)
		{
			dirState = DIR_RB;
		}
		else
		{
			dirState = DIR_L;
		}

		img->frame.y = frameY[dirState];
	}
}