#pragma once
class Bullet : public Unit
{
public:
    float           scalar;
    Vector2         fireDir;
    const float     damage = 40.0f;

public:
    Bullet();
    void Init();
    void Update();
    bool LateUpdate() override;
    void Render() override;
    bool Shoot(const shared_ptr<GameObject> player, float scalar, const Vector2 firePos);
    bool HitFrom(const string& hitter, const float damage);
};

