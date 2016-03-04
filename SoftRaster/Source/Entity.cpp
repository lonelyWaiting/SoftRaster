#include "PCH.h"
#include "Entity.h"

using namespace Sand;

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::LoadModel( std::wstring filename )
{
	m_Geometry.LoadModel( filename );
}

void Entity::SetPosition( Vector3f& Position )
{
	m_WorldMatrix = Matrix4f::TranslationMatrix( Position.x , Position.y , Position.z );
}

Matrix4f& Entity::GetWorldMatrix()
{
	return m_WorldMatrix;
}

Geometry& Entity::GetGeometry()
{
	return m_Geometry;
}