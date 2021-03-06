#pragma once
#include "txbase/fwddecl.h"
#include "txbase/shape/shape.h"
#include "txbase/math/vector.h"
#include "txbase/math/bbox.h"
#include "txbase/math/ray.h"
#include "txbase/math/transform.h"
#include "txbase/math/sample.h"

namespace TX {
	class Mesh {
	public:
		std::vector<Vec3> vertices;
		std::vector<Vec3> normals;
		std::vector<uint32_t> indices;
		std::vector<Vec2> uv;
	private:
		mutable BBox bbox_;
		mutable bool bbox_dirty_ = true;
	public:
		Mesh() {}
		Mesh(const Mesh& ot) :
			vertices(ot.vertices),
			normals(ot.normals),
			indices(ot.indices),
			uv(ot.uv) {}
		inline Mesh& operator = (const Mesh& ot) {
			vertices = ot.vertices;
			normals = ot.normals;
			indices = ot.indices;
			uv = ot.uv;
			return *this;
		}
		~Mesh() {}

		inline uint32_t VertexCount() const { return vertices.size(); }
		inline uint32_t IndexCount() const { return indices.size(); }
		inline uint32_t TriangleCount() const { return indices.size() / 3; }
		inline const uint32_t* GetIndicesOfTriangle(uint32_t triId) const { return &indices[triId * 3]; }
		inline void GetPoint(uint32_t triId, float u, float v, Vec3 *out, Vec3 *normal) const {
			const uint32_t *idx = GetIndicesOfTriangle(triId);
			const Vec3& v0 = vertices[*idx];
			const Vec3 e1 = vertices[*(++idx)] - v0;
			const Vec3 e2 = vertices[*(++idx)] - v0;
			if (out)
				*out = v0 + e1 * u + e2 * v;
			if (normal)
				*normal = Math::Normalize(Math::Cross(e1, e2));
		}
		inline const BBox& Bounds() const {
			if (!bbox_dirty_)
				return bbox_;
			bbox_ = BBox();
			for (auto& v : vertices) {
				bbox_ = Math::Union(bbox_, v);
			}
			bbox_dirty_ = false;
			return bbox_;
		}
		/// <summary>
		/// Clear the vertices, normals, texcoords and triangle indices.
		/// </summary>
		virtual void Clear();
		/// <summary>
		/// Load a sphere to this mesh.
		/// </summary>
		/// <param name="radius"> Radius of the sphere </param>
		/// <param name="slices"> Number of slices (meridian) </param>
		/// <param name="stacks"> Number of stacks (ring of latitude on xz plane) </param>
		Mesh& LoadSphere(float radius = 1.f, uint32_t slices = 72, uint32_t stacks = 48);
		/// <summary>
		/// Load a plane to this mesh.
		/// The plane faces towards z-axis.
		/// </summary>
		/// <param name="size"> Edge size </param>
		Mesh& LoadPlane(float size = 1.f);
		/// <summary>
		/// Load a cube to this mesh.
		/// </summary>
		/// <param name="size"> Edge size </param>
		Mesh& LoadCube(float size = 1.f);
		/// <summary>
		/// Apply a transform to this mesh.
		/// </summary>
		virtual void ApplyTransform(const Transform& transform);
		float Area() const;
		float Area(uint32_t triId) const;
		bool Intersect(uint32_t triId, const Ray& ray) const;
		bool Occlude(uint32_t triId, const Ray& ray) const;
	};

	class MeshSampler {
	public:
		std::shared_ptr<const Mesh> mesh;
		std::vector<float> areas;
		float sumArea, sumAreaRcp;
		std::unique_ptr<Distribution1D> areaDistro;
	public:
		MeshSampler(std::shared_ptr<const Mesh> mesh);
		inline float Area() const { return sumArea; }
		void SamplePoint(const Sample *sample, Vec3 *point, uint32_t *id, Vec3 *normal) const;

		float Pdf(uint32_t id, const Ray& wi) const;
		float Pdf(uint32_t id, const Vec3& p) const;
	};
}
