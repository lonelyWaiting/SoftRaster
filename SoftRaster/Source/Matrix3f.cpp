#include "PCH.h"
#include "Matrix3f.h"

using namespace Sand;

Matrix3f Matrix3f::RotationX( float fRadians )
{
	float fSin = sinf( fRadians );
	float fCos = cosf( fRadians );

	return Matrix3f( 1.0f , 0.0f , 0.0f ,
					 0.0f , fCos , fSin ,
					 0.0f , -fSin , fCos );
}

Matrix3f Matrix3f::RotationY( float fRadians )
{
	float fSin = sinf( fRadians );
	float fCos = cosf( fRadians );

	return Matrix3f( fCos , 0.0f , -fSin ,
					 0.0f , 1.0f , 0.0f ,
					 fSin , 0.0f , fCos );
}

Matrix3f Matrix3f::RotationZ( float fRadians )
{
	float fSin = sinf( fRadians );
	float fCos = cosf( fRadians );

	return Matrix3f( fCos , fSin , 0.0f ,
					 -fSin , fCos , 0.0f ,
					 0.0f , 0.0f , 1.0f );
}

Matrix3f Matrix3f::Rotation( Vector3f& xyz )
{
	return Matrix3f::RotationZ( xyz.z ) * Matrix3f::RotationX( xyz.x ) * Matrix3f::RotationY( xyz.y );
}

Matrix3f Matrix3f::RotationZYX( Vector3f& xyz )
{
	return Matrix3f::RotationZ( xyz.z ) * Matrix3f::RotationY( xyz.y ) * Matrix3f::RotationX( xyz.x );
}

Matrix3f Matrix3f::RotateAxis( Vector3f& Axis , float fRadians )
{
	float x = Axis.x;
	float y = Axis.y;
	float z = Axis.z;

	float Cos = cosf( fRadians );
	float OneSubCos = 1 - cosf( fRadians );
	float Sin = sinf( fRadians );

	return Matrix3f( x * x * OneSubCos + Cos , x * y * OneSubCos + z * Sin , x * z * OneSubCos - y * Sin ,
					 x * y * OneSubCos - z * Sin , y * y * OneSubCos + Cos , y * z * OneSubCos + x * Sin ,
					 x * z * OneSubCos + y * Sin , y * z * OneSubCos - x * Sin , z * z * OneSubCos + Cos );
}

void Matrix3f::Orthonormalize()
{
	// 使用施密特正交化方法
	float fInvLength = static_cast< float >( 1.0f / sqrtf( m[0] * m[0] + m[3] * m[3] + m[6] * m[6] ) );

	m[0] *= fInvLength;
	m[3] *= fInvLength;
	m[6] *= fInvLength;

	float fDot0 = m[0] * m[1] + m[3] * m[4] + m[6] * m[7];

	m[1] -= fDot0 * m[0];
	m[4] -= fDot0 * m[3];
	m[7] -= fDot0 * m[6];

	fInvLength = static_cast< float >( 1.0f / sqrtf( m[1] * m[1] + m[4] * m[4] + m[7] * m[7] ) );

	m[1] *= fInvLength;
	m[4] *= fInvLength;
	m[7] *= fInvLength;

	float fDot1 = m[0] * m[2] + m[3] * m[5] + m[6] * m[8];
	float fDot2 = m[1] * m[2] + m[4] * m[5] + m[7] * m[8];

	m[2] -= ( fDot1 * m[0] + fDot2 * m[1] );
	m[5] -= ( fDot1 * m[3] + fDot2 * m[4] );
	m[8] -= ( fDot1 * m[6] + fDot2 * m[7] );

	fInvLength = static_cast< float >( 1.0f / sqrtf( m[2] * m[2] + m[5] * m[5] + m[8] * m[8] ) );

	m[2] *= fInvLength;
	m[5] *= fInvLength;
	m[8] *= fInvLength;
}

Matrix3f Matrix3f::Identity()
{
	return Matrix3f( 1.0f , 0.0f , 0.0f ,
					 0.0f , 1.0f , 0.0f ,
					 0.0f , 0.0f , 1.0f );
}

Matrix3f Matrix3f::Transpose( Matrix3f& matrix )
{
	return Matrix3f( matrix[0] , matrix[3] , matrix[6] ,
					 matrix[1] , matrix[4] , matrix[7] ,
					 matrix[2] , matrix[5] , matrix[8] );
}

void Matrix3f::SetRow( int iRow , const Vector3f& Vector )
{
	m[iRow * 3] = Vector.x;
	m[iRow * 3 + 1] = Vector.y;
	m[iRow * 3 + 2] = Vector.z;
}

Vector3f Matrix3f::GetRow( int iRow ) const
{
	return Vector3f( m[iRow * 3 + 0] , m[iRow * 3 + 1] , m[iRow * 3 + 2] );
}

void Matrix3f::SetColumn( int iCol , const Vector3f& Vector )
{
	m[iCol] = Vector.x;
	m[3 + iCol] = Vector.y;
	m[6 + iCol] = Vector.z;
}

Vector3f Matrix3f::GetColumn( int iCol ) const
{
	return Vector3f( m[iCol] , m[3 + iCol] , m[6 + iCol] );
}