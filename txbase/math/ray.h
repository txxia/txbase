#pragma once

#include "txbase/math/vector.h"

namespace TX {
	class Ray {
	public:
		static const float EPSILON;
	public:
		Ray() : t_min(EPSILON), t_max(Math::INF){}
		Ray(const Vec3& origin, const Vec3& vdir, float t_max = Math::INF, float t_min = EPSILON) :
			origin(origin), dir(Math::Normalize(vdir)), t_min(t_min), t_max(t_max){}
		Ray(const Ray& ot) :
			origin(ot.origin), dir(ot.dir), t_min(ot.t_min), t_max(ot.t_max){}
		~Ray(){}

		Ray& operator = (const Ray& ot);
		bool operator ==(const Ray& ot);

		/// <summary>
		/// Reset the value of this ray, without normalizing direction vector.
		/// </summary>
		inline Ray& Reset(const Vec3& origin = Vec3::ZERO, const Vec3& dir = Vec3::Z, float t_max = Math::INF, float t_min = EPSILON){
			this->t_min = t_min;
			this->t_max = t_max;
			this->origin = origin;
			this->dir = dir;
			return *this;
		}

		/// <summary>
		/// Sets origin,dir,t values of this ray using two points, and normalize it.
		/// </summary>
		inline Ray& SetSegment(const Vec3& orig, const Vec3& dest, float eps_dest = EPSILON, float eps_origin = EPSILON){
			origin = orig;
			dir = dest - orig;
			t_min = eps_origin;
			t_max = Math::Length(dir);
			dir /= t_max;
			t_max = Math::Max(t_min, t_max - eps_dest);
			return *this;
		}

		/// <summary>
		/// The target point.
		/// </summary>
		inline Vec3 End() const { return origin + t_max * dir; }
	public:
		Vec3 origin;
		Vec3 dir;
		mutable float t_min, t_max;
	};

	inline std::ostream& operator << (std::ostream& os, const Ray& r){
		return os << "[" << r.origin << " -> " << r.dir << ", " << "(" << r.t_min << "~" << r.t_max << ")]";
	}

	inline Ray& Ray::operator = (const Ray& ot){
		origin = ot.origin;
		dir = ot.dir;
		t_min = ot.t_min;
		t_max = ot.t_max;
		return *this;
	}

	inline bool Ray::operator == (const Ray& ot){
		return origin == ot.origin
			&& dir == ot.dir
			&& t_min == ot.t_min
			&& t_max == ot.t_max;
	}
}
