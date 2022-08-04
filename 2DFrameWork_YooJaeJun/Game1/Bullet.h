#pragma once
class Bullet
{
public:
    ObLine		arrow;
    ObCircle    arrowPet;
    float       arrowSpeed;
    float       arrowPetSpeed;

public:
    Bullet();
    void Update(ObRect player);
    void Render();
    bool Shoot(ObRect player, const float scalar);
};

