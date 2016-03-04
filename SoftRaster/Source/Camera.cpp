#include "PCH.h"
#include "Camera.h"

using namespace Sand;

Camera::Camera()
	:m_Look( 0.0f , 0.0f , 1.0f ) , m_Up( 0.0f , 1.0f , 0.0f ) , m_Right( 1.0f , 0.0f , 0.0f ) ,
	m_fFovy( SAND_PI * 0.25f ) , m_fAspect( 800.0f / 600.0f ) , m_fNear( 1.0f ) , m_fFar( 1000.0f )
{

}

Camera::~Camera()
{

}

void Camera::SetPerspective( float fovy , float aspect , float n , float f )
{
	float t = 1.0f / tanf( fovy / 2.0f );
	float s = f / ( f - n );

	m_ProjectionMatrix = Matrix4f( t * 1.0f / aspect , 0.0f , 0.0f , 0.0f ,
								   0.0f , t , 0.0f , 0.0f ,
								   0.0f , 0.0f , s , 1.0f ,
								   0.0f , 0.0f , -n * s , 0.0f );
}

void Camera::SetOrthogonal( float width , float height , float n , float f )
{
	m_ProjectionMatrix = Matrix4f( 2.0f / width , 0.0f , 0.0f , 0.0f ,
								   0.0f , 2.0f / height , 0.0f , 0.0f ,
								   0.0f , 0.0f , 1.0f / ( f - n ) , 0.0f ,
								   0.0f , 0.0f , n / ( n - f ) , 1.0f );
}

void Camera::SetViewPosition( Vector3f& ViewPosition )
{
	m_ViewPosition = ViewPosition;
}

Matrix4f& Camera::GetViewMatrix()
{
	Vector3f At = m_ViewPosition + m_Look;
	
	m_ViewMatrix = Matrix4f::LookAtLHMatrix( m_ViewPosition , At , m_Up );

	return m_ViewMatrix;
}

Matrix4f& Camera::GetProjectMatrix()
{
	return m_ProjectionMatrix;
}

void Camera::Pitch( float Angle )
{
	/*
		ÈÆ×ÅRightÐý×ª
	*/
	Matrix3f R = Matrix3f::RotateAxis( m_Right , Angle );

	m_Up = m_Up * R;
	m_Look = m_Look * R;

	m_Look.Normalize();

	m_Right = cross( m_Up , m_Look );
	m_Right.Normalize();

	m_Up = cross( m_Look , m_Right );
	m_Up.Normalize();
}

void Camera::RotateY( float Angle )
{
	Matrix3f R = Matrix3f::RotationY( Angle );

	m_Right = m_Right * R;
	m_Look = m_Look * R;
	m_Up = m_Up * R;

	m_Look.Normalize();

	m_Right = cross( m_Up , m_Look );
	m_Right.Normalize();

	m_Up = cross( m_Look , m_Right );
	m_Up.Normalize();
}

Vector3f& Camera::GetViewPosition()
{
	return m_ViewPosition;
}

void Camera::MoveForward( float dist )
{
	m_ViewPosition += m_Look * dist;
}

void Camera::MoveBackward( float dist )
{
	m_ViewPosition -= m_Look * dist;
}

void Camera::MoveRight( float dist )
{
	m_ViewPosition += m_Right * dist;
}

void Camera::MoveLeft( float dist )
{
	m_ViewPosition -= m_Right * dist;
}