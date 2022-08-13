#pragma once
class Bullet
{
public:
    ObLine		arrow;
    ObCircle    arrowPet;
    //bool		isFired;

    float       scalar;
    Vector2     fireDir;

    float       gravity;

public:
    Bullet();
    void Update(ObRect player);
    void LateUpdate();
    void Render();
    bool Shoot(ObRect player, float scalar, Vector2 firePos);
};

