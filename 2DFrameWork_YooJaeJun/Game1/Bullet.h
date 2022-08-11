#pragma once
class Bullet
{
public:
    ObLine		hitbox;
    ObCircle    arrowPet;
    //bool		isFired;

    float       scalar;
    float       arrowPetScalar;
    Vector2     fireDir;

    float       gravity;
    float       gravityCoef;

public:
    Bullet();
    void Update(ObRect player);
    void LateUpdate();
    void Render();
    bool Shoot(ObRect player, float scalar, Vector2 firePos);
};

