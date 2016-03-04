#ifndef Renderer_h
#define Renderer_h

#include "Vector3f.h"
#include "Vector2f.h"
#include "Geometry.h"
#include "Camera.h"
#include "Texture.h"

namespace Sand
{
	class Application;

	class Renderer
	{
	public:
		Renderer( int Width , int Height , Application* pApplication );
		~Renderer();

		void ClearBackGroundColor( Color& BackColor , int Type );

		void Present();

		void LoadToBuffer( Geometry& geometry , Texture& texture );

		void SetCamera(Camera* pCamera);

		/*
			Transform To World Space
		*/
		void TransformToWorldSpace( Matrix4f& WorldMatrix );

		/*
			Transform to View Space
		*/
		void TransformToViewSpace();

		/*
			Back Face Cull
		*/
		void BackSurfaceCull();

		/*
			Project
		*/
		void TransformToProjectSpace();

		/*
			Screen
		*/
		void TransformToScreenSpace();

		/*
			Render
		*/
		void Render();

	private:
		/*
			Draw Triangle
		*/
		void DrawTriangle( int P0 , int P1 , int P2 );

		void DrawTopTriangle( float x0 , float x1 , float x2 , float y0 , float y1 , float y2 , float z0 , float z1 , float z2 , float u0 , float v0 , float u1 , float v1 , float u2 , float v2 );

		void DrawBottomTriangle( float x0 , float x1 , float x2 , float y0 , float y1 , float y2 , float z0 , float z1 , float z2 , float u0 , float v0 , float u1 , float v1 , float u2 , float v2 );

		void DrawLine( float StartX , float EndX , int Y , float StartZ , float EndZ , float u0 , float v0 , float u1 , float v1 );

		void SetColor( int x , int y , float z , float u , float v );
	private:
		int m_iWidth;
		int m_iHeight;
		BYTE* m_pScreenData;
		float* m_pScreenDepthBuffer;		// 记录深度，由于是记录1/z，范围在0.0 ~ 1.0
		Application* m_pApplication;

	protected:
		std::vector<Vector3f> PosList;
		std::vector<Vector3f> NormalList;
		std::vector<Vector2f> TexList;

		std::vector<int> IndexList;

	private:
		Camera* m_pCamera;

		Matrix3f m_TransformToScreenMatrix;

		Texture m_Texture;
	};
};
#endif