#ifndef Camera_h
#define Camera_h

#include "Matrix4f.h"

namespace Sand
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void SetPerspective( float fovy , float aspect , float n , float f );

		void SetOrthogonal( float width , float height , float n , float f );

		void SetViewPosition( Vector3f& ViewPosition );

		Matrix4f& GetViewMatrix();

		Matrix4f& GetProjectMatrix();

		void Pitch( float Angle );

		void RotateY( float Angle );

		Vector3f& GetViewPosition();

		void MoveForward( float dist );

		void MoveBackward( float dist );

		void MoveLeft( float dist );

		void MoveRight( float dist );

	protected:
		float m_fFovy;
		float m_fAspect;
		float m_fNear;
		float m_fFar;

		float m_fWidth;
		float m_fHeight;

	protected:
		Vector3f m_Look;
		Vector3f m_Up;
		Vector3f m_Right;
		Vector3f m_ViewPosition;

	protected:
		Matrix4f m_ProjectionMatrix;
		Matrix4f m_ViewMatrix;
	};
};
#endif