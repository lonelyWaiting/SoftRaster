#include "PCH.h"
#include "Application.h"
#include "Renderer.h"
#include "Vector4f.h"
#include "Matrix4f.h"

using namespace Sand;

Renderer::Renderer( int Width , int Height , Application* pApplication )
	:m_iWidth( Width ) , m_iHeight( Height ) , m_pApplication( pApplication )
{
	m_pScreenData = m_pApplication->pSurface->m_pData;

	m_pScreenDepthBuffer = new float[Width * Height];

	m_TransformToScreenMatrix = Matrix3f( 0.5f * Width	,	0				, 0 ,
										  0				,	-0.5f * Height	, 0 ,
										  0.5 * Width	,	0.5f * Height	, 1 );
}

Renderer::~Renderer()
{

}

void Renderer::ClearBackGroundColor( Color& BackColor , int Type )
{
	if ( Type & CLEAR_COLOR )
	{
		int size = m_iWidth * m_iHeight;
		for ( int i = 0 , index = 0; i < size; i++ , index += 4 )
		{
			m_pScreenData[index] = BackColor.b;
			m_pScreenData[index + 1] = BackColor.g;
			m_pScreenData[index + 2] = BackColor.r;
		}
	}
	
	if ( Type & CLEAR_DEPTH )
	{
		int size = m_iWidth * m_iHeight;

		for ( int i = 0 ; i < size; i++ )
		{
			m_pScreenDepthBuffer[i] = 1.0f;
		}
	}
}

void Renderer::LoadToBuffer( Geometry& geometry , Texture& texture )
{
	m_Texture = texture;

	if ( geometry.PosList.size() != 0 )
	{
		PosList.clear();

		PosList.insert( PosList.end() , geometry.PosList.begin() , geometry.PosList.end() );
	}

	if ( geometry.NormalList.size() != 0 )
	{
		NormalList.clear();

		NormalList.insert( NormalList.end() , geometry.NormalList.begin() , geometry.NormalList.end() );
	}

	if ( geometry.TexList.size() != 0 )
	{
		TexList.clear();

		TexList.insert( TexList.end() , geometry.TexList.begin() , geometry.TexList.end() );
	}

	if ( geometry.IndexList.size() != 0 )
	{
		IndexList.clear();
		IndexList.insert( IndexList.end() , geometry.IndexList.begin() , geometry.IndexList.end() );
	}
}

void Renderer::Present()
{
	HDC hdc = GetDC( m_pApplication->pWindow->GetHandle() );

	BitBlt( hdc , 0 , 0 , m_iWidth , m_iHeight , m_pApplication->pSurface->m_DeviceContext , 0 , 0 , SRCCOPY );

	ReleaseDC( m_pApplication->pWindow->GetHandle() , hdc );
}

void Renderer::SetCamera( Camera* pCamera )
{
	m_pCamera = pCamera;
}

void Renderer::TransformToViewSpace()
{
	Matrix4f ViewMatrix = m_pCamera->GetViewMatrix();

	int Faces = IndexList.size() / 3;

	for ( int i = 0; i < Faces; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			Vector4f Pos( PosList[IndexList[3 * i + j]] );

			PosList[IndexList[3 * i + j]] = ( Pos * ViewMatrix ).xyz();
		}
	}
}

void Renderer::BackSurfaceCull()
{
	std::vector<int> Indexs;

	int Faces = IndexList.size() / 3;

	Vector3f ViewPosition = m_pCamera->GetViewPosition();

	for ( int i = 0; i < Faces; i++ )
	{
		// 计算重心
		Vector3f A = PosList[IndexList[3 * i + 0]];
		Vector3f B = PosList[IndexList[3 * i + 1]];
		Vector3f C = PosList[IndexList[3 * i + 2]];

		Vector3f Center = Vector3f( ( A.x + B.x + C.x ) / 3.0f , ( A.y + B.y + C.y ) / 3.0f , ( A.z + B.z + C.z ) / 3.0f );

		Vector3f View = ViewPosition - Center;

		Vector3f U = B - A;
		Vector3f V = C - A;
		Vector3f N = cross( U , V );

		if ( dot( View , N ) <= 0 )
		{
			continue;
		}

		Indexs.push_back( 3 * i + 0 );
		Indexs.push_back( 3 * i + 1 );
		Indexs.push_back( 3 * i + 2 );
	}

	IndexList.clear();

	IndexList.insert( IndexList.end() , Indexs.begin() , Indexs.end() );
}

void Renderer::TransformToProjectSpace()
{
	Matrix4f ProjectMatrix = m_pCamera->GetProjectMatrix();

	int Faces = IndexList.size() / 3;

	for ( int i = 0; i < Faces; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			Vector4f V( PosList[IndexList[3 * i + j]] );

			V = V * ProjectMatrix;

			// 归一化
			V *= ( 1.0f / V.w );

			PosList[IndexList[3 * i + j]] = V.xyz();
		}
	}
}

void Renderer::TransformToWorldSpace( Matrix4f& WorldMatrix )
{
	for ( std::vector<Vector3f>::iterator iter = PosList.begin(); iter != PosList.end(); iter++ )
	{
		Vector4f Pos( *iter );
		*iter = ( Pos * WorldMatrix ).xyz();
	}

	Matrix4f Temp = WorldMatrix;
	Temp.SetTranslate( Vector3f( 0.0f , 0.0f , 0.0f ) );
	Matrix4f InvTransposeMatrix = Matrix4f::Transpose( Matrix4f::Inverse( Temp ) );

	for ( std::vector<Vector3f>::iterator iter = NormalList.begin(); iter != NormalList.end(); iter++ )
	{
		*iter = ( *iter ) * InvTransposeMatrix.GetMatrix3f();
	}
}

void Renderer::TransformToScreenSpace()
{
	for ( int i = 0; i < IndexList.size(); i += 3 )
	{
		for ( int j = 0; j < 3; j++ )
		{
			Vector3f Pos = PosList[IndexList[i + j]] *m_TransformToScreenMatrix;

			PosList[IndexList[i + j]].x = Pos.x;
			PosList[IndexList[i + j]].y = Pos.y;
		}
	}
}

void Renderer::Render()
{
	for ( int i = 0; i < IndexList.size(); i += 3 )
	{
		DrawTriangle( IndexList[i + 0] , IndexList[i + 1] , IndexList[i + 2] );
	}
}

void Renderer::DrawTriangle( int P0 , int P1 , int P2 )
{
	Vector3f v0 = PosList[P0];
	Vector3f v1 = PosList[P1];
	Vector3f v2 = PosList[P2];

	float x0 = v0.x;	float y0 = v0.y;	float z0 = v0.z;
	float x1 = v1.x;	float y1 = v1.y;	float z1 = v1.z;
	float x2 = v2.x;	float y2 = v2.y;	float z2 = v2.z;

	Vector2f Tex0 = TexList[P0];
	Vector2f Tex1 = TexList[P1];
	Vector2f Tex2 = TexList[P2];

	float s0 = Tex0.x;	float t0 = Tex0.y;
	float s1 = Tex1.x;	float t1 = Tex1.y;
	float s2 = Tex2.x;	float t2 = Tex2.y;

	if ( ( x0 == x1 && x1 == x2 ) || ( y0 == y1 && y1 == y2 ) )
	{
		return;
	}

	/*
		排序，按照y值从小到大:(x0 , y0 , z0) , (x1 , y1 , z1) , (x2 , y2 , z2)
	*/
	if ( y1 < y0 )
	{
		float temp = x1;
		x1 = x0;
		x0 = temp;

		temp = y1;
		y1 = y0;
		y0 = temp;

		temp = z1;
		z1 = z0;
		z0 = temp;

		temp = s0;
		s0 = s1;
		s1 = temp;

		temp = t0;
		t0 = t1;
		t1 = temp;
	}

	if ( y2 < y0 )
	{
		float temp = x2;
		x2 = x0;
		x0 = temp;

		temp = y2;
		y2 = y0;
		y0 = temp;

		temp = z2;
		z2 = z0;
		z0 = temp;

		temp = s0;
		s0 = s2;
		s2 = temp;

		temp = t0;
		t0 = t2;
		t2 = temp;
	}

	if ( y2 < y1 )
	{
		float temp = y2;
		y2 = y1;
		y1 = temp;

		temp = x2;
		x2 = x1;
		x1 = temp;

		temp = z2;
		z2 = z1;
		z1 = temp;

		temp = s1;
		s1 = s2;
		s2 = temp;

		temp = t1;
		t1 = t2;
		t2 = temp;
	}

	if ( y0 == y1 )
	{
		// 平顶三角形
		DrawTopTriangle( x0 , x1 , x2 , y0 , y1 , y2 , z0 , z1 , z2 , s0 , t0 , s1 , t1 , s2 , t2 );
	}
	else if ( y1 == y2 )
	{
		// 平底三角形
		DrawBottomTriangle( x0 , x1 , x2 , y0 , y1 , y2 , z0 , z1 , z2 , s0 , t0 , s1 , t1 , s2 , t2 );
	}
	else
	{
		float NewX = x0 + ( y1 - y0 ) * ( x2 - x0 ) / ( y2 - y0 );
		float NewZ = z0 + ( y1 - y0 ) * ( z2 - z0 ) / ( y2 - y0 );
		float NewS = s0 + ( y1 - y0 ) * ( s2 - s0 ) / ( y2 - y0 );
		float NewT = t0 + ( y1 - y0 ) * ( t2 - t0 ) / ( y2 - y0 );
		DrawBottomTriangle( x0 , NewX , x1 , y0 , y1 , y1 , z0 , NewZ , z1 , s0 , t0 , NewS , NewT , s1 , t1 );
		DrawTopTriangle( x1 , NewX , x2 , y1 , y1 , y2 , z0 , NewZ , z2 , s1 , t1 , NewS , NewT , s2 , t2 );
	}
}

/*
	绘制平顶三角形

  (x0 , y0)		(x1 , y1)	
	____________
	\          /
	 \        /
	  \      /
	   \    /
		\  /
		 \/
		(x2 , y2)
*/    
void Renderer::DrawTopTriangle( float x0 , float x1 , float x2 , float y0 , float y1 , float y2 , float z0 , float z1 , float z2 , float u0 , float v0 , float u1 , float v1 , float u2 , float v2 )
{
	float temp;

	// 确保x1 > x0
	if ( x1 < x0 )
	{
		temp = x0;
		x0 = x1;
		x1 = temp;

		temp = z1;
		z1 = z0;
		z0 = temp;

		temp = u0;
		u0 = u1;
		u1 = temp;

		temp = v0;
		v0 = v1;
		v1 = temp;
	}

	float Height = y2 - y0;

	float LeftDx = ( x2 - x0 ) / Height;
	float RightDx = ( x2 - x1 ) / Height;
	float LeftDz = ( z2 - z0 ) / Height;
	float RightDz = ( z2 - z1 ) / Height;
	float LeftDu = ( u2 - u0 ) / Height;
	float LeftDv = ( v2 - v0 ) / Height;
	float RightDu = ( u2 - u1 ) / Height;
	float RightDv = ( v2 - v1 ) / Height;

	int StartY = Ceiling( y0 );
	int EndY = Ceiling( y2 ) - 1;

	float StartX = x0 + ( StartY - y0 ) * LeftDx;
	float EndX = x1 + ( StartY - y0 ) * RightDx;

	float StartZ = z0 + ( StartY - y0 ) * LeftDz;
	float EndZ = z1 + ( StartY - y0 ) * RightDz;

	float StartU = u0 + ( StartY - y0 ) * LeftDu;
	float StartV = v0 + ( StartY - y0 ) * LeftDv;

	float EndU = u1 + ( StartY - y0 ) * RightDu;
	float EndV = v1 + ( StartY - y0 ) * RightDv;

	for ( int y = StartY; y <= EndY; y++ )
	{
		DrawLine( StartX , EndX , y , StartZ , EndZ , StartU , StartV , EndU , EndV );

		StartX += LeftDx;
		EndX += RightDx;

		StartZ += LeftDz;
		EndZ += RightDz;

		StartU += LeftDu;
		EndU += RightDu;

		StartV += LeftDv;
		EndV += RightDv;
	}
}

/*
	绘制平底三角形
	`````
	   (x0 , y0)
		  /\
		 /  \
		/    \
	   /      \
	  /        \
	 /          \
	/____________\
(x1 , y1)		(x2 , y2)
*/
void Renderer::DrawBottomTriangle( float x0 , float x1 , float x2 , float y0 , float y1 , float y2 , float z0 , float z1 , float z2 , float u0 , float v0 , float u1 , float v1 , float u2 , float v2 )
{
	float temp;
	if ( x1 > x2 )
	{
		temp = x2;
		x2 = x1;
		x1 = temp;

		temp = z1;
		z1 = z2;
		z2 = temp;

		temp = u1;
		u1 = u2;
		u2 = temp;

		temp = v1;
		v1 = v2;
		v2 = temp;
	}

	float Height = y2 - y0;

	float LeftDx = ( x1 - x0 ) / Height;
	float RightDx = ( x2 - x0 ) / Height;
	float LeftDz = ( z1 - z0 ) / Height;
	float RightDz = ( z2 - z0 ) / Height;
	float LeftDu = ( u1 - u0 ) / Height;
	float LeftDv = ( v1 - v0 ) / Height;
	float RightDu = ( u2 - u0 ) / Height;
	float RightDv = ( v2 - v0 ) / Height;


	int StartY = Ceiling( y0 );
	int EndY = Ceiling( y2 ) - 1;

	// 修正由y的变化带来的误差
	float StartX = x0 + ( StartY - y0 ) * LeftDx;
	float EndX = x0 + ( StartY - y0 ) * RightDx;

	float StartZ = z0 + ( StartY - y0 ) * LeftDz;
	float EndZ = z0 + ( StartY - y0 ) * RightDz;

	float StartU = u0 + ( StartY - y0 ) * LeftDu;
	float StartV = v0 + ( StartY - y0 ) * LeftDv;

	float EndU = u0 + ( StartY - y0 ) * RightDu;
	float EndV = v0 + ( StartY - y0 ) * RightDv;

	for ( int y = StartY; y <= EndY; y++ )
	{
		DrawLine( StartX , EndX , y , StartZ , EndZ , StartU , StartV , EndU , EndV );

		StartX += LeftDx;
		EndX += RightDx;

		StartZ += LeftDz;
		EndZ += RightDz;

		StartU += LeftDu;
		EndU += RightDu;

		StartV += LeftDv;
		EndV += RightDv;
	}
}

void Renderer::DrawLine( float StartX , float EndX , int Y , float StartZ , float EndZ , float u0 , float v0 , float u1 , float v1 )
{
	float ZDX = ( float )( EndZ - StartZ ) / ( float )( EndX - StartX );
	float UDX = ( float )( u1 - u0 ) / ( float )( EndX - StartX );
	float VDX = ( float )( v1 - v0 ) / ( float )( EndX - StartX );

	int xs = Ceiling( StartX );
	int xe = Ceiling( EndX ) - 1;
	
	float zs = ( xs - StartX ) * ZDX + StartZ;
	float us = ( xs - StartX ) * UDX + u0;
	float vs = ( xs - StartX ) * VDX + v0;

	for ( int X = xs; X <= xe; X++ )
	{
		/*
			暂时没添加颜色插值。。
			添加一下深度比较
		*/
		SetColor( X , Y , zs , us , vs );

		zs += ZDX;
		us += UDX;
		vs += VDX;
	}
}

void Renderer::SetColor( int x , int y , float z , float u , float v )
{
	if ( ( x >= m_iWidth || x < 0 ) || ( y >= m_iHeight || y < 0 ) )
	{
		return;
	}

	if ( z < m_pScreenDepthBuffer[y * m_iWidth + x] )
	{
		int index = y * m_iWidth + x;
		m_pScreenDepthBuffer[index] = z;

		Color c = m_Texture.GetColorNearest( u , v );

		index *= 4;
		m_pScreenData[index + 0] = c.b;
		m_pScreenData[index + 1] = c.g;
		m_pScreenData[index + 2] = c.r;
	}
}