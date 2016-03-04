#ifndef Entity_h
#define Entity_h

#include "Vector3f.h"
#include "Matrix4f.h"
#include "Geometry.h"

namespace Sand
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		void LoadModel( std::wstring filename );

		void SetPosition( Vector3f& Position );

		Geometry& GetGeometry();

		Matrix4f& GetWorldMatrix();

	protected:
		Geometry m_Geometry;
		Matrix4f m_WorldMatrix;
	};
};
#endif