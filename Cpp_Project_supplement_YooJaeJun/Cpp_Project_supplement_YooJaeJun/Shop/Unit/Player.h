#pragma once
#include <unordered_map>
#include <string>
#include "Unit.h"

class Player : public Unit
{
public:
	Player() = default;

public:
	virtual void printItemList() override;
};

