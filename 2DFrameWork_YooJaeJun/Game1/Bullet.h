#pragma once
class Bullet
{
public:
    ObLine		arrow;
    ObCircle    arrowPet;

public:
    Bullet();
    void Update(ObRect player);
    void Render();
    bool Shoot(ObRect player);
};

