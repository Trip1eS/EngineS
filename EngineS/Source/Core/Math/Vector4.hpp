#pragma once

#include "Math.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

namespace EngineS {

class Vector4 {
  public:
	float x {0.0f};
	float y {0.0f};
	float z {0.0f};
	float w {0.0f};

	static const Vector4 Zero;
	static const Vector4 One;

  public:
	Vector4() = default;
	Vector4(float x, float y, float z, float w) : x {x}, y {y}, z {z}, w {w} {}
	Vector4(const Vector3& v3, float w);
	explicit Vector4(float coords[4]) : x {coords[0]}, y {coords[1]}, z {coords[2]}, w {coords[3]} {}

	float operator[](size_t i) const {
		assert(i < 4);
		return *(&x + i);
	}

	float& operator[](size_t i) {
		assert(i < 4);
		return *(&x + i);
	}

	float*		 Data() { return &x; }
	const float* Data() const { return &x; }

	void Set(float newX, float newY, float newZ, float newW) {
		x = newX;
		y = newY;
		z = newZ;
		w = newW;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector4& v) {
		os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
		return os;
	}

	bool operator==(const Vector4& rhs) const { return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w); }

	bool operator!=(const Vector4& rhs) const { return !(rhs == *this); }

	Vector4 operator+(const Vector4& rhs) const { return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
	Vector4 operator-(const Vector4& rhs) const { return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
	Vector4 operator*(float scalar) const { return Vector4(x * scalar, y * scalar, z * scalar, w * scalar); }
	Vector4 operator*(const Vector4& rhs) const { return Vector4(rhs.x * x, rhs.y * y, rhs.z * z, rhs.w * w); }
	Vector4 operator/(float scalar) const {
		assert(scalar != 0.0);
		return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
	}
	Vector4 operator/(const Vector4& rhs) const {
		assert(rhs.x != 0 && rhs.y != 0 && rhs.z != 0 && rhs.w != 0);
		return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
	}

	const Vector4& operator+() const { return *this; }

	Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }

	friend Vector4 operator*(float scalar, const Vector4& rhs) {
		return Vector4(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z, scalar * rhs.w);
	}

	friend Vector4 operator/(float scalar, const Vector4& rhs) {
		assert(rhs.x != 0 && rhs.y != 0 && rhs.z != 0 && rhs.w != 0);
		return Vector4(scalar / rhs.x, scalar / rhs.y, scalar / rhs.z, scalar / rhs.w);
	}

	friend Vector4 operator+(const Vector4& lhs, float rhs) {
		return Vector4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
	}

	friend Vector4 operator+(float lhs, const Vector4& rhs) {
		return Vector4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
	}

	Vector4& operator+=(const Vector4& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	Vector4& operator-=(const Vector4& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	Vector4& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	Vector4& operator*=(const Vector4& rhs) {
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}

	Vector4& operator/=(float scalar) {
		assert(scalar != 0.0);

		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}

	Vector4& operator/=(const Vector4& rhs) {
		assert(rhs.x != 0 && rhs.y != 0 && rhs.z != 0);
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	static float Dot(const Vector4& a, const Vector4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
};

} // namespace EngineS