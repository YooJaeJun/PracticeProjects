#pragma once
class Bullet
{
public:
    ObCircle	hitbox;

    float       scalar;
    Vector2     fireDir;

    float       gravity;

public:
    Bullet();
    void Update(ObCircle player);
    void LateUpdate();
    void Render();
    bool Shoot(ObCircle player, float scalar, Vector2 firePos);
};

