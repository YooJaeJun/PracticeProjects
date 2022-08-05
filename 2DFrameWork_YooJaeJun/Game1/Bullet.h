#pragma once
class Bullet
{
public:
    ObLine		arrow;
    ObCircle    arrowPet;
    float       arrowScalar;
    float       arrowPetScalar;

public:
    Bullet();
    void Update(ObRect player);
    void Render();
    bool Shoot(ObRect player, const float scalar);
};

