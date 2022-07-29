#pragma once
class Bullet
{
public:
    ObLine		arrow;
    bool		isFired;
    ObCircle    arrowPet;

public:
    Bullet();
    void Update();
    void Render();
};

