#include "PCH.h"
#include "Vector4f.h"

using namespace Sand;

Vector3f Vector4f::xyz() const
{
	return Vector3f( x , y , z );
}

Vector2f Vector4f::xy() const
{
	return Vector2f( x , y );
}