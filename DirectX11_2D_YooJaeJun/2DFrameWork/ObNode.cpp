#include "framework.h"

bool ObNode::almostEqualNode(const ObNode& ohter)
{
    return almostEqualFloat(x, ohter.x) && almostEqualFloat(y, ohter.y);
}

float ObNode::DirToRadian(ObNode Dir)
{
    //���� �������Ͱ� �ƴ϶��
    Vector2 vDir = Vector2(Dir.x, Dir.y);
    vDir.Normalize();
    return atan2f(vDir.y, vDir.x);
}