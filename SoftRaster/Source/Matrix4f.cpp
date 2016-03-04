#include "PCH.h"
#include "Matrix4f.h"

using namespace Sand;

Matrix4f Matrix4f::Inverse( Matrix4f& matrix )
{
	float fA0 = matrix[0] * matrix[5] - matrix[1] * matrix[4];
	float fA1 = matrix[0] * matrix[6] - matrix[2] * matrix[4];
	float fA2 = matrix[0] * matrix[7] - matrix[3] * matrix[4];
	float fA3 = matrix[1] * matrix[6] - matrix[2] * matrix[5];
	float fA4 = matrix[1] * matrix[7] - matrix[3] * matrix[5];
	float fA5 = matrix[2] * matrix[7] - matrix[3] * matrix[6];
	float fB0 = matrix[8] * matrix[13] - matrix[9] * matrix[12];
	float fB1 = matrix[8] * matrix[14] - matrix[10] * matrix[12];
	float fB2 = matrix[8] * matrix[15] - matrix[11] * matrix[12];
	float fB3 = matrix[9] * matrix[14] - matrix[10] * matrix[13];
	float fB4 = matrix[9] * matrix[15] - matrix[11] * matrix[13];
	float fB5 = matrix[10] * matrix[15] - matrix[14] * matrix[11];

	Matrix4f temp;

	temp[0] = +matrix[5] * fB5 - matrix[6] * fB4 + matrix[7] * fB3;
	temp[4] = -matrix[4] * fB5 + matrix[6] * fB2 - matrix[7] * fB1;
	temp[8] = +matrix[4] * fB4 - matrix[5] * fB2 + matrix[7] * fB0;
	temp[12] = -matrix[4] * fB3 + matrix[5] * fB1 - matrix[6] * fB0;

	temp[1] = -matrix[1] * fB5 + matrix[2] * fB4 - matrix[3] * fB3;
	temp[5] = +matrix[0] * fB5 - matrix[2] * fB2 + matrix[3] * fB1;
	temp[9] = -matrix[0] * fB4 + matrix[1] * fB2 - matrix[3] * fB0;
	temp[13] = +matrix[0] * fB3 - matrix[1] * fB1 + matrix[2] * fB0;

	temp[2] = +matrix[13] * fA5 - matrix[14] * fA4 + matrix[15] * fA3;
	temp[6] = -matrix[12] * fA5 + matrix[14] * fA2 - matrix[15] * fA1;
	temp[10] = +matrix[12] * fA4 - matrix[13] * fA2 + matrix[15] * fA0;
	temp[14] = -matrix[12] * fA3 + matrix[13] * fA1 - matrix[14] * fA0;

	temp[3] = -matrix[9] * fA5 + matrix[10] * fA4 - matrix[11] * fA3;
	temp[7] = +matrix[8] * fA5 - matrix[10] * fA2 + matrix[11] * fA1;
	temp[11] = -matrix[8] * fA4 + matrix[9] * fA2 - matrix[11] * fA0;
	temp[15] = +matrix[8] * fA3 - matrix[9] * fA1 + matrix[10] * fA0;

	float fDet = fA0 * fB5 - fA1 * fB4 + fA2 * fB3 + fA3 * fB2 - fA4 * fB1 + fA5 * fB0;

	float fInvDet = ( ( float )1.0f ) / fDet;
	for ( int iRow = 0; iRow < 4; iRow++ )
	{
		for ( int iCol = 0; iCol < 4; iCol++ )
		{
			temp[iRow * 4 + iCol] *= fInvDet;
		}
	}

	return temp;
}

Vector3f Matrix4f::GetBasisX() const
{
	return Vector3f( m00 , m01 , m02 );
}

Vector3f Matrix4f::GetBasisY() const
{
	return Vector3f( m10 , m11 , m12 );
}

Vector3f Matrix4f::GetBasisZ() const
{
	return Vector3f( m20 , m21 , m22 );
}

Vector3f Matrix4f::GetTranslate() const
{
	return Vector3f( m30 , m31 , m32 );
}

void Matrix4f::SetTranslate( const Vector3f& Trans )
{
	m30 = Trans[0];	m31 = Trans[1];	m32 = Trans[2];
}

void Matrix4f::SetRotation( const Matrix3f& Rot )
{
	m00 = Rot[0];	m01 = Rot[1];	m02 = Rot[2];
	m10 = Rot[3];	m11 = Rot[4];	m12 = Rot[5];
	m20 = Rot[6];	m21 = Rot[7];	m22 = Rot[8];
}

Matrix4f Matrix4f::RotationMatrixXYZ( float fRadiansX , float fRadiansY , float fRadiansZ )
{
	return Matrix4f::RotationMatrixZ( fRadiansZ ) * Matrix4f::RotationMatrixY( fRadiansY ) * Matrix4f::RotationMatrixX( fRadiansX );
}

Matrix4f Matrix4f::RotationMatrixX( float fRadians )
{
	Matrix4f ret;

	float fSin = sinf( fRadians );
	float fCos = cosf( fRadians );

	ret[0] = 1.0f;	ret[1] = 0.0f;	ret[2] = 0.0f;	ret[3] = 0.0f;
	ret[4] = 0.0f;	ret[5] = fCos;	ret[6] = fSin;	ret[7] = 0.0f;
	ret[8] = 0.0f;	ret[9] = -fSin;	ret[10] = fCos;	ret[11] = 0.0f;
	ret[12] = 0.0f;	ret[13] = 0.0f;	ret[14] = 0.0f;	ret[15] = 1.0f;

	return ret;
}

Matrix4f Matrix4f::RotationMatrixY( float fRadians )
{
	Matrix4f ret;

	float fSin = sinf( fRadians );
	float fCos = cosf( fRadians );

	ret[0] = fCos;	ret[1] = 0.0f;	ret[2] = -fSin;	ret[3] = 0.0f;
	ret[4] = 0.0f;	ret[5] = 1.0f;	ret[6] = 0.0f;	ret[7] = 0.0f;
	ret[8] = fSin;	ret[9] = 0.0f;	ret[10] = fCos;	ret[11] = 0.0f;
	ret[12] = 0.0f;	ret[13] = 0.0f;	ret[14] = 0.0f;	ret[15] = 1.0f;

	return ret;
}

Matrix4f Matrix4f::RotationMatrixZ( float fRadians )
{
	Matrix4f ret;

	float fSin = sinf( fRadians );
	float fCos = cosf( fRadians );

	ret[0] = fCos;	ret[1] = fSin;	ret[2] = 0.0f;	ret[3] = 0.0f;
	ret[4] = -fSin;	ret[5] = fCos;	ret[6] = 0.0f;	ret[7] = 0.0f;
	ret[8] = 0.0f;	ret[9] = 0.0f;	ret[10] = 1.0f;	ret[11] = 0.0f;
	ret[12] = 0.0f;	ret[13] = 0.0f;	ret[14] = 0.0f;	ret[15] = 1.0f;

	return ret;
}

Matrix4f Matrix4f::ScaleMatrix( const Vector3f& scale )
{
	return Matrix4f( scale.x , 0.0f , 0.0f , 0.0f ,
					 0.0f , scale.y , 0.0f , 0.0f ,
					 0.0f , 0.0f , scale.z , 0.0f ,
					 0.0f , 0.0f , 0.0f , 1.0f );
}

Matrix4f Matrix4f::ScaleMatrix( float fScale )
{
	return Matrix4f( fScale , 0.0f , 0.0f , 0.0f ,
					 0.0f , fScale , 0.0f , 0.0f ,
					 0.0f , 0.0f , fScale , 0.0f ,
					 0.0f , 0.0f , 0.0f , 1.0f );
}

Matrix4f Matrix4f::ScaleMatrixXYZ( float fX , float fY , float fZ )
{
	return Matrix4f( fX , 0.0f , 0.0f , 0.0f ,
					 0.0f , fY , 0.0f , 0.0f ,
					 0.0f , 0.0f , fZ , 0.0f ,
					 0.0f , 0.0f , 0.0f , 1.0f );
}

Matrix4f Matrix4f::TranslationMatrix( float fX , float fY , float fZ )
{
	return Matrix4f( 1.0f , 0.0f , 0.0f , 0.0f ,
					 0.0f , 1.0f , 0.0f , 0.0f ,
					 0.0f , 0.0f , 1.0f , 0.0f ,
					 fX , fY , fZ , 1.0f );
}

Matrix4f Matrix4f::LookAtLHMatrix( Vector3f& eye , Vector3f& at , Vector3f& up )
{
	/*
	Æ½ÒÆ¾ØÕó
	|1		0		0		0|
	|0		1		0		0|
	|0		0		1		0|
	|-cam_x	-cam_y	-cam_z	1|

	Ðý×ªÓëËõ·Å¾ØÕó
	|right.x	up.x	look.x		0|
	|right.y	up.y	look.y		0|
	|right.z	up.z	look.z		0|
	|0			0		0			1|


	ViewMatrix
	|1		0		0		0|			|right.x	up.x	look.x		0|
	|0		1		0		0|			|right.y	up.y	look.y		0|
	|0		0		1		0|	*		|right.z	up.z	look.z		0|
	|-cam_x	-cam_y	-cam_z	1|			|0			0		0			1|
	=
	|right.x			up.x			look.x			0|
	|right.y			up.y			look.y			0|
	|right.z			up.z			look.z			0|
	|-cam * right		-cam * up		-cam * look		1|
	*/
	Matrix4f ret;

	Vector3f zAxis = at - eye;
	zAxis.Normalize();

	Vector3f xAxis = cross( up , zAxis );
	xAxis.Normalize();

	Vector3f yAxis = cross( zAxis , xAxis );

	ret.m[0] = xAxis.x;		ret.m[1] = yAxis.x;		ret.m[2] = zAxis.x;		ret.m[3] = 0.0f;
	ret.m[4] = xAxis.y;		ret.m[5] = yAxis.y;		ret.m[6] = zAxis.y;		ret.m[7] = 0.0f;
	ret.m[8] = xAxis.z;		ret.m[9] = yAxis.z;		ret.m[10] = zAxis.z;	ret.m[11] = 0.0f;

	ret.m[12] = -( dot( xAxis , eye ) );

	ret.m[13] = -( dot( yAxis , eye ) );

	ret.m[14] = -( dot( zAxis , eye ) );

	ret.m[15] = 1.0f;

	return ret;
}

Matrix4f Matrix4f::PerspectiveFovLHMatrix( float fovy , float aspect , float zn , float zf )
{
	Matrix4f ret;

	float tanY = tan( fovy / 2.0f );
	if ( 0.0f == tanY )	tanY = 0.001f;
	float yScale = 1.0f / tanY;

	if ( 0.0f == aspect )	aspect = 0.001f;
	float xScale = yScale / aspect;

	float range = zf / ( zf - zn );

	ret.m[0] = xScale;		ret.m[1] = 0.0f;	ret.m[2] = 0.0f;					ret.m[3] = 0.0f;
	ret.m[4] = 0.0f;		ret.m[5] = yScale;	ret.m[6] = 0.0f;					ret.m[7] = 0.0f;
	ret.m[8] = 0.0f;		ret.m[9] = 0.0f;	ret.m[10] = range;					ret.m[11] = 1.0f;
	ret.m[12] = 0.0f;		ret.m[13] = 0.0f;	ret.m[14] = -range * zn;			ret.m[15] = 0.0f;

	return ret;
}

Matrix4f Matrix4f::OrthographicLHMatrix( float zn , float zf , float width , float height )
{
	Matrix4f ret;

	if ( zn == zf )	zf = zn + 0.1f;

	if ( width <= 0.0f )		width = 1.0f;
	if ( height <= 0.0f )	height = 1.0f;

	ret.m[0] = 2.0f / width;	ret.m[1] = 0.0f;			ret.m[2] = 0.0f;					ret.m[3] = 0.0f;
	ret.m[4] = 0.0f;			ret.m[5] = 2.0f / height;	ret.m[6] = 0.0f;					ret.m[7] = 0.0f;
	ret.m[8] = 0.0f;			ret.m[9] = 0.0f;			ret.m[10] = 1.0f / ( zf - zn );		ret.m[11] = 0.0f;
	ret.m[12] = 0.0f;			ret.m[13] = 0.0f;			ret.m[14] = zn / ( zn - zf );		ret.m[15] = 1.0f;

	return ret;
}

Matrix4f Matrix4f::Transpose( Matrix4f& matrix )
{
	return Matrix4f( matrix[0] , matrix[4] , matrix[8] , matrix[12] ,
					 matrix[1] , matrix[5] , matrix[9] , matrix[13] ,
					 matrix[2] , matrix[6] , matrix[10] , matrix[14] ,
					 matrix[3] , matrix[7] , matrix[11] , matrix[15] );
}

void Matrix4f::SetRow( int iRow , const Vector4f& Vector )
{
	m[iRow * 4 + 0] = Vector.x;
	m[iRow * 4 + 1] = Vector.y;
	m[iRow * 4 + 2] = Vector.z;
	m[iRow * 4 + 3] = Vector.w;
}

void Matrix4f::SetRow( int iRow , const Vector3f& Vector )
{
	m[iRow * 4 + 0] = Vector.x;
	m[iRow * 4 + 1] = Vector.y;
	m[iRow * 4 + 2] = Vector.z;
}

void Matrix4f::SetColumn( int iCol , const Vector4f& Vector )
{
	m[iCol] = Vector.x;
	m[4 + iCol] = Vector.y;
	m[8 + iCol] = Vector.z;
	m[12 + iCol] = Vector.w;
}

Vector4f Matrix4f::GetRow( int iRow ) const
{
	return Vector4f( m[4 * iRow + 0] , m[4 * iRow + 1] , m[4 * iRow + 2] , m[4 * iRow + 3] );
}

Vector4f Matrix4f::GetColumn( int iCol ) const
{
	return Vector4f( m[iCol] , m[4 + iCol] , m[8 + iCol] , m[12 + iCol] );
}

Matrix4f Matrix4f::Identity()
{
	return Matrix4f( 1.0f , 0.0f , 0.0f , 0.0f ,
					 0.0f , 1.0f , 0.0f , 0.0f ,
					 0.0f , 0.0f , 1.0f , 0.0f ,
					 0.0f , 0.0f , 0.0f , 1.0f );
}

Matrix3f Matrix4f::GetMatrix3f()
{
	return Matrix3f( m00 , m01 , m02 ,
					 m10 , m11 , m12 ,
					 m20 , m21 , m22 );
}
