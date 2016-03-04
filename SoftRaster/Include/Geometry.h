#ifndef Geometry_h
#define Geometry_h

#include "Vector3f.h"
#include "Vector2f.h"
#include "Texture.h"

namespace Sand
{
	class Geometry
	{
	public:
		void LoadModel( std::wstring filename );

	private:
		std::array<int , 3> ToIndexTriple( const std::string s );

	public:
		std::vector<Vector3f> PosList;
		std::vector<Vector3f> NormalList;
		std::vector<Vector2f> TexList;

		std::vector<int> IndexList;

		Texture m_Texture;
	};
};
#endif