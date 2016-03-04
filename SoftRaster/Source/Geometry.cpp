#include "PCH.h"
#include "Geometry.h"
#include "FileSystem.h"
#include "Log.h"
#include "ObjFormat.h"
#include "SandString.h"

using namespace Sand;

void Geometry::LoadModel( std::wstring filename )
{
	FileSystem fs;
	filename = fs.GetModelFolder() + filename;

	std::ifstream fin( filename , std::ios::in );
	if ( !fin.is_open() )
	{
		Log::Get().Write( L"open obj model file failed!" );
	}

	std::vector<Vector3f> Positions;
	std::vector<Vector3f> Normals;
	std::vector<Vector2f> Texcoords;
	std::string MaterialLibs;

	std::vector<ObjFace> Faces;

	std::string lines;

	while ( std::getline( fin , lines ) )
	{
		std::stringstream lineStream( lines );
		std::string token;
		std::vector<std::string> tokenList;

		// 提取字符串
		while ( lineStream >> token )
		{
			tokenList.push_back( token );
		}

		if ( tokenList.size() != 0 )
		{
			// 顶点数据
			if ( tokenList[0] == "v" )
			{
				Positions.emplace_back( Vector3f( static_cast< float >( atof( tokenList[1].c_str() ) ) ,
					static_cast< float >( atof( tokenList[2].c_str() ) ) ,
					static_cast< float >( atof( tokenList[3].c_str() ) ) ) );
			}
			// 法线
			else if ( tokenList[0] == "vn" )
			{
				Normals.emplace_back( Vector3f( static_cast< float >( atof( tokenList[1].c_str() ) ) ,
					static_cast< float >( atof( tokenList[2].c_str() ) ) ,
					static_cast< float >( atof( tokenList[3].c_str() ) ) ) );
			}
			else if ( tokenList[0] == "vt" )
			{
				Texcoords.emplace_back( Vector2f( static_cast< float >( atof( tokenList[1].c_str() ) ) ,
					static_cast< float >( atof( tokenList[2].c_str() ) ) ) );
			}
			else if ( tokenList[0] == "mtllib" )
			{
				MaterialLibs = lines.substr( 7 );
			}
			else if ( tokenList[0] == "f" )
			{
				ObjFace face;

				for ( int i = 0; i < 3; i++ )
				{
					// 使用'/'作为分隔符，将数据提取出来
					auto triple = ToIndexTriple( tokenList[i + 1] );

					face.PositionIndices[i] = triple[0];
					face.CoordinateIndices[i] = triple[1];
					face.NormalIndices[i] = triple[2];
				}

				Faces.emplace_back( face );
			}
		}
	}

	fin.close();

	// ----------------------------解析MTL---------------------------------
	{
		std::wstring MTLFilename = fs.GetModelFolder() + SandString::ToUnicode( MaterialLibs );

		std::ifstream fin( MTLFilename , std::ios::in );
		if ( !fin.is_open() )
		{
			Log::Get().Write( L"open obj file failed" );
			return;
		}

		std::string line;

		while ( std::getline( fin , line ) )
		{
			std::stringstream lineStream( line );
			std::string token;
			std::vector<std::string> tokenList;

			// 提取字符串
			while ( lineStream >> token )
			{
				tokenList.push_back( token );
			}

			if ( tokenList.size() != 0 )
			{
				if ( tokenList[0] == "map_Kd" )
				{
					m_Texture.LoadTexture( SandString::ToUnicode( tokenList[1] ) );
				}
			}
		}
	}

	if ( Positions.size() != 0 )
	{
		float x , y , z;

		for ( int i = 0; i < Faces.size(); i++ )
		{
			// ---------------------第一个顶点------------------------
			x = Positions[Faces[i].PositionIndices[0]].x;
			y = Positions[Faces[i].PositionIndices[0]].y;
			z = Positions[Faces[i].PositionIndices[0]].z;
			PosList.push_back( Vector3f( x , y , z ) );

			// ---------------------第二个顶点------------------------------
			x = Positions[Faces[i].PositionIndices[1]].x;
			y = Positions[Faces[i].PositionIndices[1]].y;
			z = Positions[Faces[i].PositionIndices[1]].z;
			PosList.push_back( Vector3f( x , y , z ) );

			// ---------------------第三个顶点------------------------------
			x = Positions[Faces[i].PositionIndices[2]].x;
			y = Positions[Faces[i].PositionIndices[2]].y;
			z = Positions[Faces[i].PositionIndices[2]].z;
			PosList.push_back( Vector3f( x , y , z ) );
		}
	}

	if ( Normals.size() != 0 )
	{
		float x , y , z;

		for ( int i = 0; i < Faces.size(); i++ )
		{
			// ---------------------第一个顶点------------------------
			x = Normals[Faces[i].NormalIndices[0]].x;
			y = Normals[Faces[i].NormalIndices[0]].y;
			z = Normals[Faces[i].NormalIndices[0]].z;
			NormalList.push_back( Vector3f( x , y , z ) );

			// ---------------------第二个顶点------------------------------
			x = Normals[Faces[i].NormalIndices[1]].x;
			y = Normals[Faces[i].NormalIndices[1]].y;
			z = Normals[Faces[i].NormalIndices[1]].z;
			NormalList.push_back( Vector3f( x , y , z ) );

			// ---------------------第三个顶点------------------------------
			x = Normals[Faces[i].NormalIndices[2]].x;
			y = Normals[Faces[i].NormalIndices[2]].y;
			z = Normals[Faces[i].NormalIndices[2]].z;
			NormalList.push_back( Vector3f( x , y , z ) );
		}

		// 归一化
		for ( int i = 0; i < NormalList.size(); i++ )
		{
			NormalList[i].Normalize();
		}
	}

	if ( Texcoords.size() != 0 )
	{
		float x , y;

		for ( int i = 0; i < Faces.size(); i++ )
		{
			// ---------------------第一个顶点------------------------
			x = Texcoords[Faces[i].CoordinateIndices[0]].x;
			y = Texcoords[Faces[i].CoordinateIndices[0]].y;
			TexList.push_back( Vector2f( x , y ) );

			// ---------------------第二个顶点------------------------------
			x = Texcoords[Faces[i].CoordinateIndices[1]].x;
			y = Texcoords[Faces[i].CoordinateIndices[1]].y;
			TexList.push_back( Vector2f( x , y ) );

			// ---------------------第三个顶点------------------------------
			x = Texcoords[Faces[i].CoordinateIndices[2]].x;
			y = Texcoords[Faces[i].CoordinateIndices[2]].y;
			TexList.push_back( Vector2f( x , y ) );
		}
	}

	for ( int i = 0; i < Faces.size(); i++ )
	{
		IndexList.push_back( 3 * i + 0);
		IndexList.push_back( 3 * i + 1 );
		IndexList.push_back( 3 * i + 2 );
	}
}

std::array<int , 3> Geometry::ToIndexTriple( const std::string s )
{
	std::vector<std::string> elements;
	std::stringstream ss( s );
	std::string item;

	// 将ss以'/'为分隔符，item保存分割后的string
	while ( std::getline( ss , item , '/' ) )
	{
		elements.push_back( item );
	}

	assert( elements.size() >= 1 && elements.size() <= 3 );

	std::array<int , 3> triple = { 0 , 0 , 0 };

	for ( int i = 0; i < elements.size(); i++ )
	{
		triple[i] = atoi( elements[i].c_str() ) - 1;
	}

	return triple;
}