#include <math.h>
#include <limits>
#include <type_traits>

const float almost_equal_float(const float x, const float y, int ulp = 2);

const float almost_equal_vector(const Vector2& v1, const Vector2& v2);

// Utility ���� �浹�� ���
int ccw(const Vector2& v1, const Vector2& v2, const Vector2& v3);