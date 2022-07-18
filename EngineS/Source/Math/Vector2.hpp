#pragma once

#include "Math.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

namespace EngineS {

class Vector2 {
  public:
	float x {0.0f}, y {0.0f};

	static const Vector2 Down;
	static const Vector2 Left;
	static const Vector2 NegativeInfinity;
	static const Vector2 One;
	static const Vector2 PositiveInfinity;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Zero;

  public:
	Vector2() = default;
	Vector2(float x, float y) : x {x}, y {y} {}
	explicit Vector2(float scalar) : x {scalar}, y {scalar} {}

	explicit operator Vector3() const;

	float*		 Data() { return &x; }
	const float* Data() const { return &x; }

	void Set(float newX, float newY) {
		x = newX;
		y = newY;
	}

	float operator[](size_t i) const {
		assert(i < 2);
		return (i == 0 ? x : y);
	}
	float& operator[](size_t i) {
		assert(i < 2);
		return (i == 0 ? x : y);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
		os << "Vector2(" << v.x << ", " << v.y << ")";
		return os;
	}

	bool operator==(const Vector2& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const Vector2& rhs) const { return x != rhs.x || y != rhs.y; }

	Vector2 operator+(const Vector2& rhs) const { return {x + rhs.x, y + rhs.y}; }
	Vector2 operator-(const Vector2& rhs) const { return {x - rhs.x, y - rhs.y}; }
	Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
	Vector2 operator*(const Vector2& rhs) const { return {x * rhs.x, y * rhs.y}; }
	Vector2 operator/(float scalar) const {
		assert(scalar != 0.0f);
		float inv = 1.0f / scalar;
		return {x * inv, y * inv};
	}
	Vector2 operator/(const Vector2& rhs) const { return {x / rhs.x, y / rhs.y}; }

	Vector2& operator+=(const Vector2& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Vector2& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	Vector2& operator*=(const Vector2& rhs) {
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	Vector2& operator/=(float scalar) {
		assert(scalar != 0.0);
		float inv = 1.0f / scalar;
		x *= inv;
		y *= inv;
		return *this;
	}
	Vector2& operator/=(const Vector2& rhs) {
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}
	friend Vector2 operator*(float scalar, const Vector2& rhs) { return {scalar * rhs.x, scalar * rhs.y}; }

	float Magnitude() const { return std::hypot(x, y); }
	float SqrMagnitude() const { return x * x + y * y; }

	Vector2 Normalized() const {
		Vector2 ret = *this;
		ret.Normalize();
		return ret;
	}
	void Normalize() {
		float length = Magnitude();
		if (length == 0.0f)
			return;
		float invLength = 1.0f / length;
		*this *= invLength;
	}

	static float   Distance(const Vector2& a, const Vector2& b) { return (b - a).Magnitude(); }
	static float   SqrDistance(const Vector2& a, const Vector2& b) { return (b - a).SqrMagnitude(); }
	static float   Dot(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }
	static Vector2 Lerp(const Vector2& lhs, const Vector2& rhs, float alpha) { return lhs + alpha * (rhs - lhs); }
	static Vector2 Perpendicular(const Vector2& inDir) { return {-inDir.y, inDir.x}; }
	static Vector2 Reflect(const Vector2& in, const Vector2& normal) { return in - (2 * Dot(in, normal) * normal); }
};

} // namespace EngineS
