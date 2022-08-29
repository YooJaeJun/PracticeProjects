#pragma once
class Item : public Brick
{
public:
	float	colorTime;
	float	fireTime;
	bool	end;

public:
	Item() = default;
};

