#pragma once

#include <cstdint>
#include <iostream>
#include "txbase/math/base.h"

namespace TX
{
	template<size_t N, typename T>
	class Vec {
	public:
		T v[N];

		inline Vec(){}
		explicit inline Vec(const T& val){ for (auto i = 0; i < N; i++) v[i] = val; }
		inline Vec(const Vec& ot){ this->operator=(ot); }
		inline Vec& operator = (const Vec& ot){
			for (auto i = 0; i < N; i++)
				v[i] = ot[i];
			return *this;
		}
		template<typename U> inline Vec(const Vec<N, U>& ot){ this->operator=<U>(ot); }
		template<typename U> inline Vec& operator = (const Vec<N, U>& ot){
			for (auto i = 0; i < N; i++)
				v[i] = T(ot[i]);
			return *this;
		}
		inline const T& operator [] (const size_t i) const { assert(i < N); return v[i]; }
		inline       T& operator [] (const size_t i)       { assert(i < N); return v[i]; }
		inline explicit operator const T*() const { return v; }
		inline explicit operator       T*()       { return v; }
		inline bool operator == (const Vec& rhs) const {
			for (auto i = 0; i < N; i++)
				if (v[i] != rhs[i])
					return false;
			return true;
		}
	};
	template<size_t N, typename T>
	inline std::ostream& operator << (std::ostream& os, const Vec<N, T>& v){
		os << "(";
		for (auto i = 0; i < N - 1; i++)
			os << v[i] << ", ";
		return os << v[N-1] << ")";
	}


	template <typename T>
	class Vec <2, T> {
	public:
		union{
			struct { T x, y; };
			struct { T u, v; };
			T data[2];
		};
		static const Vec ZERO;
		static const Vec ONE;
		static const Vec X;
		static const Vec Y;
		static const Vec UNIT[2];
	public:
		inline Vec() : x(Math::ZERO), y(Math::ZERO){}
		inline Vec(const Vec& ot) : x(ot.x), y(ot.y){}
		explicit inline Vec(T val) : x(val), y(val){}
		inline Vec(const T& x, const T& y) : x(x), y(y){}
		template<size_t N>
		inline Vec(const Vec<N, T>& ot) : x(ot.x), y(ot.y) { static_assert(N >= 2, "Dimension increase is not supported"); }
		inline Vec& operator = (const Vec& ot) { x = ot.x, y = ot.y; return *this; }
		template<typename U>
		inline Vec(const Vec<2, U>& ot) : x(T(ot.x)), y(T(ot.y)){}
		template<typename U>
		inline Vec& operator = (const Vec<2, U>& ot){ x = T(ot.x), y = T(ot.y); return *this; }

		inline const T& operator [] (const size_t i) const { return data[i]; }
		inline       T& operator [] (const size_t i)       { return data[i]; }

		inline explicit operator const T*() const { return data; }
		inline explicit operator       T*()       { return data; }

		inline bool operator == (const Vec& ot) const { return x == ot.x && y == ot.y; }
		inline bool operator != (const Vec& ot) const { return x != ot.x || y != ot.y; }
		inline bool operator < (const Vec& ot) const { return x < ot.x && y < ot.y; }
		inline bool operator > (const Vec& ot) const { return x > ot.x && y > ot.y; }
		inline bool operator <= (const Vec& ot) const { return x <= ot.x && y <= ot.y; }
		inline bool operator >= (const Vec& ot) const { return x >= ot.x && y >= ot.y; }

		inline Vec operator + () const { return Vec(+x, +y); }
		inline Vec operator - () const { return Vec(-x, -y); }
		inline Vec operator + (const T& s) const { return Vec(x + s, y + s); }
		inline Vec operator + (const Vec& ot) const { return Vec(x + ot.x, y + ot.y); }
		inline Vec operator - (const T& s) const { return Vec(x - s, y - s); }
		inline Vec operator - (const Vec& ot) const { return Vec(x - ot.x, y - ot.y); }
		inline Vec operator * (const T& s) const { return Vec(x * s, y * s); }
		inline Vec operator * (const Vec& ot) const { return Vec(x * ot.x, y * ot.y); }
		inline Vec operator / (const T& s) const { return operator*(T(Math::ONE) / s); }
		inline Vec operator / (const Vec& ot) const { return Vec(x / ot.x, y / ot.y); }

		inline const Vec& operator += (const Vec& ot) { x += ot.x; y += ot.y; return *this; }
		inline const Vec& operator -= (const Vec& ot) { x -= ot.x; y -= ot.y; return *this; }
		inline const Vec& operator *= (const T& s) { x *= s; y *= s; return *this; }
		inline const Vec& operator *= (const Vec& ot) { x *= ot.x; y *= ot.y; return *this; }
		inline const Vec& operator /= (const T& s) { return operator*=(T(Math::ONE) / s); }
		inline const Vec& operator /= (const Vec& ot) { x /= ot.x; y /= ot.y; return *this; }
	};

	template <typename T> const Vec<2, T> Vec<2, T>::ZERO((T)Math::ZERO);
	template <typename T> const Vec<2, T> Vec<2, T>::ONE((T)Math::ONE);
	template <typename T> const Vec<2, T> Vec<2, T>::X(Math::ONE, Math::ZERO);
	template <typename T> const Vec<2, T> Vec<2, T>::Y(Math::ZERO, Math::ONE);
	template <typename T> const Vec<2, T> Vec<2, T>::UNIT[2] = {
		Vec<2, T>(Math::ONE, Math::ZERO),
		Vec<2, T>(Math::ZERO, Math::ONE)
	};

	template <typename T>
	inline std::ostream& operator << (std::ostream& os, const Vec<2, T>& v){ return os << "(" << v.x << ", " << v.y << ")"; }
	template <typename T>
	inline Vec<2, T> operator * (const T& s, const Vec<2, T>& v) { return v * s; }

	namespace Math {
		template <typename T>
		inline Vec<2, T> Abs(const Vec<2, T>& v) { return Vec4(Abs(v.x), Abs(v.y)); }
		template <typename T>
		inline T Dot(const Vec<2, T>& u, const Vec<2, T>& v) { return u.x * v.x + u.y * v.y; }
		template <typename T>
		inline T AbsDot(const Vec<2, T>& u, const Vec<2, T>& v) { return Abs(Dot(u, v)); }
		template <typename T>
		inline T LengthSqr(const Vec<2, T>& v) { return Dot(v, v); }
		template <typename T>
		inline float Length(const Vec<2, T>& v) { return Sqrt(LengthSqr(v)); }
		template <typename T>
		inline T DistSqr(const Vec<2, T>& u, const Vec<2, T>& v){ return LengthSqr(u - v); }
		template <typename T>
		inline float Dist(const Vec<2, T>& u, const Vec<2, T>& v){ return Length(u - v); }
		template <typename T>
		inline Vec<2, T> Normalize(const Vec<2, T>& v) { return v * Rsqrt(LengthSqr(v)); }
		template <typename T>
		inline Vec<2, T> Min(const Vec<2, T>& v1, const Vec<2, T>& v2) { return Vec<2, T>(Min(v1.x, v2.x), Min(v1.y, v2.y)); }
		template <typename T>
		inline Vec<2, T> Max(const Vec<2, T>& v1, const Vec<2, T>& v2) { return Vec<2, T>(Max(v1.x, v2.x), Max(v1.y, v2.y)); }
		template <typename T>
		inline Vec<2, T> Lerp(float t, const Vec<2, T>& v1, const Vec<2, T>& v2) { return Vec<2, T>(Lerp(t, v1.x, v2.x), Lerp(t, v1.y, v2.y)); }
	}

	template <typename T>
	class Vec <3, T> {
	public:
		union{
			struct{ T x, y, z; };
			T data[3];
		};
		static const Vec X;
		static const Vec Y;
		static const Vec Z;
		static const Vec UNIT[3];
		static const Vec ZERO;
		static const Vec ONE;
		static const Vec PI;
		static const Vec PI_RCP;
		static const Vec BACK;
		static const Vec DOWN;
		static const Vec FORWARD;
		static const Vec LEFT;
		static const Vec RIGHT;
		static const Vec UP;
	public:
		inline Vec() : x(Math::ZERO), y(Math::ZERO), z(Math::ZERO){}
		explicit inline Vec(const T& val) : x(val), y(val), z(val){}
		inline Vec(const T& x, const T& y, const T& z) : x(x), y(y), z(z){}
		inline Vec(const Vec& ot) : x(ot.x), y(ot.y), z(ot.z){}
		inline Vec(const Vec<2, T>& ot, T z) : x(ot.x), y(ot.y), z(z){}
		template<size_t N>
		inline Vec(const Vec<N, T>& ot) : x(ot.x), y(ot.y), z(ot.z) { static_assert(N >= 3, "Dimension increase is not supported"); }
		inline Vec& operator = (const Vec& ot) { x = ot.x, y = ot.y, z = ot.z; return *this; }
		template<typename U>
		inline Vec(const Vec<3, U>& ot) : x(T(ot.x)), y(T(ot.y)), z(T(ot.z)) {}
		template<typename U>
		inline Vec& operator = (const Vec<3, U>& ot) { x = T(ot.x), y = T(ot.y), z = T(ot.z); return *this; }

		inline const T& operator [] (const size_t i) const { return data[i]; }
		inline		 T& operator [] (const size_t i)	   { return data[i]; }

		inline explicit operator const T*() const { return data; }
		inline explicit operator	   T*()       { return data; }

		inline bool operator == (const Vec& ot) const { return x == ot.x && y == ot.y && z == ot.z; }
		inline bool operator != (const Vec& ot) const { return x != ot.x || y != ot.y || z != ot.z; }
		inline bool operator < (const Vec& ot)	const { return x < ot.x && y < ot.y && z < ot.z; }
		inline bool operator > (const Vec& ot)	const { return x > ot.x && y > ot.y && z > ot.z; }
		inline bool operator <= (const Vec& ot) const { return x <= ot.x && y <= ot.y && z <= ot.z; }
		inline bool operator >= (const Vec& ot) const { return x >= ot.x && y >= ot.y && z >= ot.z; }

		inline Vec operator + ()				const { return Vec(+x, +y, +z); }
		inline Vec operator - ()				const { return Vec(-x, -y, -z); }
		inline Vec operator + (const Vec& ot)	const { return Vec(x + ot.x, y + ot.y, z + ot.z); }
		inline Vec operator - (const Vec& ot)	const { return Vec(x - ot.x, y - ot.y, z - ot.z); }
		inline Vec operator * (const T& s)				const { return Vec(x * s, y * s, z * s); }
		inline Vec operator * (const Vec& ot)	const { return Vec(x * ot.x, y * ot.y, z * ot.z); }
		inline Vec operator / (const T& s)				const { return operator*(T(Math::ONE) / s); }
		inline Vec operator / (const Vec& ot)	const { return Vec(x / ot.x, y / ot.y, z / ot.z); }
		inline Vec& operator += (const Vec& ot) { x += ot.x; y += ot.y; z += ot.z; return *this; }
		inline Vec& operator -= (const Vec& ot) { x -= ot.x; y -= ot.y; z -= ot.z; return *this; }
		inline Vec& operator *= (const T& s) { x *= s; y *= s; z *= s; return *this; }
		inline Vec& operator *= (const Vec& ot) { x *= ot.x; y *= ot.y; z *= ot.z; return *this; }
		inline Vec& operator /= (const T& s) { return operator*=(T(Math::ONE) / s); }
		inline Vec& operator /= (const Vec& ot) { x /= ot.x; y /= ot.y; z /= ot.z; return *this; }
	};

	template <typename T> const Vec<3, T> Vec<3, T>::ZERO((T)Math::ZERO);
	template <typename T> const Vec<3, T> Vec<3, T>::ONE((T)Math::ONE);
	template <typename T> const Vec<3, T> Vec<3, T>::X(Math::ONE, Math::ZERO, Math::ZERO);
	template <typename T> const Vec<3, T> Vec<3, T>::Y(Math::ZERO, Math::ONE, Math::ZERO);
	template <typename T> const Vec<3, T> Vec<3, T>::Z(Math::ZERO, Math::ZERO, Math::ONE);
	template <typename T> const Vec<3, T> Vec<3, T>::UNIT[3] = {
		Vec<3, T>(Math::ONE, Math::ZERO, Math::ZERO),
		Vec<3, T>(Math::ZERO, Math::ONE, Math::ZERO),
		Vec<3, T>(Math::ZERO, Math::ZERO, Math::ONE)
	};
	template <typename T> const Vec<3, T> Vec<3, T>::BACK(Math::ZERO, Math::ZERO, Math::ONE);
	template <typename T> const Vec<3, T> Vec<3, T>::FORWARD(Math::ZERO, Math::ZERO, -T(Math::ONE));
	template <typename T> const Vec<3, T> Vec<3, T>::LEFT(-T(Math::ONE), Math::ZERO, Math::ZERO);
	template <typename T> const Vec<3, T> Vec<3, T>::RIGHT(Math::ONE, Math::ZERO, Math::ZERO);
	template <typename T> const Vec<3, T> Vec<3, T>::DOWN(Math::ZERO, -T(Math::ONE), Math::ZERO);
	template <typename T> const Vec<3, T> Vec<3, T>::UP(Math::ZERO, Math::ONE, Math::ZERO);

	template <typename T>
	inline std::ostream& operator << (std::ostream& os, const Vec<3, T>& v){ return os << "(" << v.x << ", " << v.y << ", " << v.z << ")"; }
	template <typename T>
	inline Vec<3, T> operator * (const T& s, const Vec<3, T>& v) { return v * s; }

	namespace Math {
		template <typename T>
		inline Vec<3, T> Abs(const Vec<3, T>& v) { return Vec4(Abs(v.x), Abs(v.y), Abs(v.z)); }
		template <typename T>
		inline Vec<3, T> Cross(const Vec<3, T>& lhs, const Vec<3, T>& rhs) {
			return Vec<3, T>(
				lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x);
		}
		template <typename T>
		inline T Dot(const Vec<3, T>& u, const Vec<3, T>& v) { return u.x * v.x + u.y * v.y + u.z * v.z; }
		template <typename T>
		inline T AbsDot(const Vec<3, T>& u, const Vec<3, T>& v) { return Abs(Dot(u, v)); }
		template <typename T>
		inline T LengthSqr(const Vec<3, T>& v) { return Dot(v, v); }
		template <typename T>
		inline float Length(const Vec<3, T>& v) { return Sqrt(LengthSqr(v)); }
		template <typename T>
		inline T DistSqr(const Vec<3, T>& u, const Vec<3, T>& v) { return LengthSqr(u - v); }
		template <typename T>
		inline float Dist(const Vec<3, T>& u, const Vec<3, T>& v) { return Length(u - v); }
		template <typename T>
		inline Vec<3, T> Normalize(const Vec<3, T>& v) { return v * Rsqrt(LengthSqr(v)); }
		template <typename T>
		inline Vec<3, T> Min(const Vec<3, T>& v1, const Vec<3, T>& v2) { return Vec<3, T>(Min(v1.x, v2.x), Min(v1.y, v2.y), Min(v1.z, v2.z)); }
		template <typename T>
		inline Vec<3, T> Max(const Vec<3, T>& v1, const Vec<3, T>& v2) { return Vec<3, T>(Max(v1.x, v2.x), Max(v1.y, v2.y), Max(v1.z, v2.z)); }
		template <typename T>
		inline Vec<3, T> ToRad(const Vec<3, T>& v) { return Vec<3, T>(ToRad(v.x), ToRad(v.y), ToRad(v.z)); }
		template <typename T>
		inline Vec<3, T> ToDeg(const Vec<3, T>& v) { return Vec<3, T>(ToDeg(v.x), ToDeg(v.y), ToDeg(v.z)); }
		template <typename T>
		inline Vec<3, T> Lerp(float t, const Vec<3, T>& v1, const Vec<3, T>& v2) { return Vec<3, T>(Lerp(t, v1.x, v2.x), Lerp(t, v1.y, v2.y), Lerp(t, v1.z, v2.z)); }
		template <typename T>
		inline Vec<3, T> Slerp(float t, const Vec<3, T>& v1, const Vec<3, T>& v2) {
			// Normalize v1, v2
			float mag1 = Length(v1), mag2 = Length(v2);
			Vec<3, T> v1n = v1 / mag1, v2n = v2 / mag2;
			// Clamp into the range of Acos()
			float dot = Clamp(Dot(v1n, v2n), -1.0f, 1.0f);
			// Interpolate the angle
			float theta = Acos(dot) * t;
			// Interpolate the magnitude
			float mag = Lerp(t, mag1, mag2);
			// Result
			Vec<3, T> relativeVec = Normalize(v2n - v1n * dot);
			return (v1n * Cos(theta) + relativeVec * Sin(theta)) * mag;
		}
	}

	template <typename T>
	class Vec <4, T> {
	public:
		union{
			struct { T x, y, z, w; };
			T data[4];
		};
		static const Vec X;
		static const Vec Y;
		static const Vec Z;
		static const Vec W;
		static const Vec UNIT[4];
		static const Vec ZERO;
		static const Vec ONE;
		static const Vec PI;
		static const Vec PI_RCP;
	public:
		inline Vec() : x(Math::ZERO), y(Math::ZERO), z(Math::ZERO), w(Math::ZERO){}
		explicit inline Vec(const T& val) : x(val), y(val), z(val), w(val){}
		inline Vec(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w){}
		inline Vec(const Vec<2, T>& a, const Vec<2, T>& b) : x(a.x), y(a.y), z(b.x), w(b.y){}
		inline Vec(const T *arr) : x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3]){}
		inline Vec(const Vec& ot) : x(ot.x), y(ot.y), z(ot.z), w(ot.w){}
		inline Vec(const Vec<3, T>& ot, T w) : x(ot.x), y(ot.y), z(ot.z), w(w){}
		template<size_t N>
		inline Vec(const Vec<N, T>& ot) : x(ot.x), y(ot.y), z(ot.z), w(ot.w) { static_assert(N >= 4, "Dimension increase is not supported"); }
		inline Vec& operator = (const Vec& ot) { x = ot.x, y = ot.y, z = ot.z, w = ot.w; return *this; }
		template<typename U>
		inline Vec(const Vec<4, U>& ot) : x(T(ot.x)), y(T(ot.y)), z(T(ot.z)), w(T(ot.w)) {}
		template<typename U>
		inline Vec& operator = (const Vec<4, U>& ot) { x = T(ot.x), y = T(ot.y), z = T(ot.z), w = T(ot.w); return *this; }

		inline const T& operator [] (const size_t i) const { return data[i]; }
		inline		 T& operator [] (const size_t i)	   { return data[i]; }

		inline explicit operator const T*() const { return data; }
		inline explicit operator       T*()       { return data; }

		inline bool operator == (const Vec& ot) const { return x == ot.x && y == ot.y && z == ot.z && w == ot.w; }
		inline bool operator != (const Vec& ot) const { return x != ot.x || y != ot.y || z != ot.z || w != ot.w; }

		inline const Vec operator + () const { return Vec(+x, +y, +z, +w); }
		inline const Vec operator - () const { return Vec(-x, -y, -z, -w); }
		inline const Vec operator + (const Vec& ot) const { return Vec(x + ot.x, y + ot.y, z + ot.z, w + ot.w); }
		inline const Vec operator - (const Vec& ot) const { return Vec(x - ot.x, y - ot.y, z - ot.z, w - ot.w); }
		inline const Vec operator * (const T& s) const { return Vec(x * s, y * s, z * s, w * s); }
		inline const Vec operator * (const Vec& ot) const { return Vec(x * ot.x, y * ot.y, z * ot.z, w * ot.w); }
		inline const Vec operator / (const T& s) const { return operator*(T(Math::ONE) / s); }
		inline const Vec operator / (const Vec& ot) const { return Vec(x / ot.x, y / ot.y, z / ot.z, w / ot.w); }
		inline Vec& operator += (const Vec& ot) { x += ot.x; y += ot.y; z += ot.z; w += ot.w; return *this; }
		inline Vec& operator -= (const Vec& ot) { x -= ot.x; y -= ot.y; z -= ot.z; w -= ot.w; return *this; }
		inline Vec& operator *= (const T& s) { x *= s; y *= s; z *= s; w *= s; return *this; }
		inline Vec& operator *= (const Vec& ot) { x *= ot.x; y *= ot.y; z *= ot.z; w *= ot.w; return *this; }
		inline Vec& operator /= (const T& s) { return operator*=(T(Math::ONE) / s); }
		inline Vec& operator /= (const Vec& ot) { x /= ot.x; y /= ot.y; z /= ot.z; w /= ot.w; return *this; }
	};
	template <typename T>
	inline std::ostream& operator << (std::ostream& os, const Vec<4, T>& v)	{ return os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")"; }
	template <typename T>
	inline Vec<4, T> operator * (const T& s, const Vec<4, T>& v) { return v * s; }

	template <typename T> const Vec<4, T> Vec<4, T>::ZERO(Math::ZERO);
	template <typename T> const Vec<4, T> Vec<4, T>::ONE(Math::ONE);
	template <typename T> const Vec<4, T> Vec<4, T>::X(Math::ONE, Math::ZERO, Math::ZERO, Math::ZERO);
	template <typename T> const Vec<4, T> Vec<4, T>::Y(Math::ZERO, Math::ONE, Math::ZERO, Math::ZERO);
	template <typename T> const Vec<4, T> Vec<4, T>::Z(Math::ZERO, Math::ZERO, Math::ONE, Math::ZERO);
	template <typename T> const Vec<4, T> Vec<4, T>::W(Math::ZERO, Math::ZERO, Math::ZERO, Math::ONE);
	template <typename T> const Vec<4, T> Vec<4, T>::UNIT[4] = {
		Vec<4, T>(Math::ONE, Math::ZERO, Math::ZERO, Math::ZERO),
		Vec<4, T>(Math::ZERO, Math::ONE, Math::ZERO, Math::ZERO),
		Vec<4, T>(Math::ZERO, Math::ZERO, Math::ONE, Math::ZERO),
		Vec<4, T>(Math::ZERO, Math::ZERO, Math::ZERO, Math::ONE)
	};

	namespace Math {
		template <typename T>
		inline Vec<4, T> Abs(const Vec<4, T>& v) { return Vec<4, T>(Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w)); }
		template <typename T>
		inline T Dot(const Vec<4, T>& u, const Vec<4, T>& v) { return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w; }
		template <typename T>
		inline T AbsDot(const Vec<4, T>& u, const Vec<4, T>& v) { return Abs(Dot(u, v)); }
		template <typename T>
		inline T LengthSqr(const Vec<4, T>& v) { return Dot(v, v); }
		template <typename T>
		inline float Length(const Vec<4, T>& v) { return Sqrt(LengthSqr(v)); }
		template <typename T>
		inline T DistSqr(const Vec<4, T>& u, const Vec<4, T>& v) { return LengthSqr(u - v); }
		template <typename T>
		inline float Dist(const Vec<4, T>& u, const Vec<4, T>& v) { return Length(u - v); }
		template <typename T>
		inline Vec<4, T> Normalize(const Vec<4, T>& v) { return v * Rsqrt(LengthSqr(v)); }
		template <typename T>
		inline Vec<4, T> Min(const Vec<4, T>& v1, const Vec<4, T>& v2) { return Vec<4, T>(Min(v1.x, v2.x), Min(v1.y, v2.y), Min(v1.z, v2.z), Min(v1.w, v2.w)); }
		template <typename T>
		inline Vec<4, T> Max(const Vec<4, T>& v1, const Vec<4, T>& v2) { return Vec<4, T>(Max(v1.x, v2.x), Max(v1.y, v2.y), Max(v1.z, v2.z), Max(v1.w, v2.w)); }
		template <typename T>
		inline Vec<4, T> Lerp(float t, const Vec<4, T>& v1, const Vec<4, T>& v2) { return Vec<4, T>(Lerp(t, v1.x, v2.x), Lerp(t, v1.y, v2.y), Lerp(t, v1.z, v2.z), Lerp(t, v1.w, v2.w)); }
	}

	typedef Vec<2, float> Vec2;
	typedef Vec<2, int> Vec2i;
	typedef Vec<2, uint32_t> Vec2u;
	typedef Vec<3, float> Vec3;
	typedef Vec<3, int> Vec3i;
	typedef Vec<3, uint32_t> Vec3u;
	typedef Vec<4, float> Vec4;
	typedef Vec<4, int> Vec4i;
	typedef Vec<4, uint32_t> Vec4u;
}
