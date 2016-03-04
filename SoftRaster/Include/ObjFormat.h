#ifndef ObjFormat_h
#define ObjFormat_h

#include <vector>
#include <array>
#include "Vector2f.h"
#include "Vector3f.h"

namespace Sand
{
	struct ObjFace
	{
		std::array<int , 3> PositionIndices;
		std::array<int , 3> NormalIndices;
		std::array<int , 3> CoordinateIndices;
	};

	struct ObjSubObject
	{
		std::string MaterialName;
		std::vector<ObjFace> Faces;

		ObjSubObject()
		{
			MaterialName = "";
		}
	};

	struct ObjObject
	{
		std::string name;
		std::vector<ObjSubObject> SubObjects;
	};
};
#endif