#pragma once
class Bullet : public Unit
{
public:
    float       scalar;
    Vector2     fireDir;

public:
    Bullet();
    void Init();
    void Update(ObCircle player);
    bool LateUpdate() override;
    void Render() override;
    bool Shoot(ObCircle player, float scalar, Vector2 firePos);
    bool HitFrom(const float damage);
};

