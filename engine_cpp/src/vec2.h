#pragma once

template <typename T> class Vec2 {
  public:
    T x;
    T y;

    Vec2<T> operator+(const Vec2<T> &v) { return {x + v.x, y + v.y}; }

    Vec2<T> operator-(const Vec2<T> &v) { return {x - v.x, y - v.y}; }

    Vec2<T> operator*(T scalar) { return {x * scalar, y * scalar}; }

    Vec2<T> operator/(T scalar) { return {x / scalar, y / scalar}; }
};

using Vec2i = Vec2<int>;
