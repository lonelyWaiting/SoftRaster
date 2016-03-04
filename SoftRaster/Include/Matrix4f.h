#ifndef Matrix4f_H
#define Matrix4f_H

#include "Matrix3f.h"
#include "Vector4f.h"

namespace Sand
{
	class Matrix4f
	{
	public:
		inline Matrix4f()
			: m00( 1 ) , m01( 0 ) , m02( 0 ) , m03( 0 ) ,
			m10( 0 ) , m11( 1 ) , m12( 0 ) , m13( 0 ) ,
			m20( 0 ) , m21( 0 ) , m22( 1 ) , m23( 0 ) ,
			m30( 0 ) , m31( 0 ) , m32( 0 ) , m33( 1 )
		{

		}

		inline Matrix4f( const float arr[4][4] )
		{
			memcpy( m , arr , 16 * sizeof( float ) );
		}

		inline Matrix4f( const float arr[16] )
		{
			memcpy( m , arr , 16 * sizeof( float ) );
		}

		inline Matrix4f( float _m00 , float _m01 , float _m02 , float _m03 ,
						 float _m10 , float _m11 , float _m12 , float _m13 ,
						 float _m20 , float _m21 , float _m22 , float _m23 ,
						 float _m30 , float _m31 , float _m32 , float _m33 )
		{
			m00 = _m00;	m01 = _m01;	m02 = _m02;	m03 = _m03;

			m10 = _m10;	m11 = _m11;	m12 = _m12;	m13 = _m13;

			m20 = _m20;	m21 = _m21;	m22 = _m22; m23 = _m23;

			m30 = _m30;	m31 = _m31;	m32 = _m32;	m33 = _m33;
		}

		inline Matrix4f( const Matrix4f& matrix )
		{
			memcpy( m , matrix.m , 16 * sizeof( float ) );
		}

	public:
		inline Matrix4f& operator= ( const Matrix4f& rhs )
		{
			memcpy( this->m , rhs.m , 16 * sizeof( float ) );

			return *this;
		}

		Matrix4f operator* ( const Matrix4f& rhs ) const
		{
			return Matrix4f( m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 + m03 * rhs.m30 ,
							 m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 + m03 * rhs.m31 ,
							 m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 + m03 * rhs.m32 ,
							 m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03 * rhs.m33 ,

							 m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 + m13 * rhs.m30 ,
							 m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31 ,
							 m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32 ,
							 m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33 ,

							 m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 + m23 * rhs.m30 ,
							 m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31 ,
							 m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32 ,
							 m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33 ,

							 m30 * rhs.m00 + m31 * rhs.m10 + m32 * rhs.m20 + m33 * rhs.m30 ,
							 m30 * rhs.m01 + m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31 ,
							 m30 * rhs.m02 + m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32 ,
							 m30 * rhs.m03 + m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33 );
		}

		Matrix4f& operator*= ( const Matrix4f& rhs )
		{
			Matrix4f temp = *this;

			m00 = temp.m00 * rhs.m00 + temp.m01 * rhs.m10 + temp.m02 * rhs.m20 + temp.m03 * rhs.m30;
			m01 = temp.m00 * rhs.m01 + temp.m01 * rhs.m11 + temp.m02 * rhs.m21 + temp.m03 * rhs.m31;
			m02 = temp.m00 * rhs.m02 + temp.m01 * rhs.m12 + temp.m02 * rhs.m22 + temp.m03 * rhs.m32;
			m03 = temp.m00 * rhs.m03 + temp.m01 * rhs.m13 + temp.m02 * rhs.m23 + temp.m03 * rhs.m33;

			m10 = temp.m10 * rhs.m00 + temp.m11 * rhs.m10 + temp.m12 * rhs.m20 + temp.m13 * rhs.m30;
			m11 = temp.m10 * rhs.m01 + temp.m11 * rhs.m11 + temp.m12 * rhs.m21 + temp.m13 * rhs.m31;
			m12 = temp.m10 * rhs.m02 + temp.m11 * rhs.m12 + temp.m12 * rhs.m22 + temp.m13 * rhs.m32;
			m13 = temp.m10 * rhs.m03 + temp.m11 * rhs.m13 + temp.m12 * rhs.m23 + temp.m13 * rhs.m33;

			m20 = temp.m20 * rhs.m00 + temp.m21 * rhs.m10 + temp.m22 * rhs.m20 + temp.m23 * rhs.m30;
			m21 = temp.m20 * rhs.m01 + temp.m21 * rhs.m11 + temp.m22 * rhs.m21 + temp.m23 * rhs.m31;
			m22 = temp.m20 * rhs.m02 + temp.m21 * rhs.m12 + temp.m22 * rhs.m22 + temp.m23 * rhs.m32;
			m23 = temp.m20 * rhs.m03 + temp.m21 * rhs.m13 + temp.m22 * rhs.m23 + temp.m23 * rhs.m33;

			m30 = temp.m30 * rhs.m00 + temp.m31 * rhs.m10 + temp.m32 * rhs.m20 + temp.m33 * rhs.m30;
			m31 = temp.m30 * rhs.m01 + temp.m31 * rhs.m11 + temp.m32 * rhs.m21 + temp.m33 * rhs.m31;
			m32 = temp.m30 * rhs.m02 + temp.m31 * rhs.m12 + temp.m32 * rhs.m22 + temp.m33 * rhs.m32;
			m33 = temp.m30 * rhs.m03 + temp.m31 * rhs.m13 + temp.m32 * rhs.m23 + temp.m33 * rhs.m33;

			return *this;
		}

		inline friend Vector4f operator* ( const Vector4f& lhs , const Matrix4f& rhs )
		{
			return Vector4f( lhs.x * rhs.m00 + lhs.y * rhs.m10 + lhs.z * rhs.m20 + lhs.w * rhs.m30 ,
							 lhs.x * rhs.m01 + lhs.y * rhs.m11 + lhs.z * rhs.m21 + lhs.w * rhs.m31 ,
							 lhs.x * rhs.m02 + lhs.y * rhs.m12 + lhs.z * rhs.m22 + lhs.w * rhs.m32 ,
							 lhs.x * rhs.m03 + lhs.y * rhs.m13 + lhs.z * rhs.m23 + lhs.w * rhs.m33 );
		}

		inline bool operator== ( const Matrix4f& Matrix ) const
		{
			return ( memcmp( m , Matrix.m , 4 * 4 * sizeof( float ) ) == 0 );
		}

		inline bool operator!= ( const Matrix4f& Matrix ) const
		{
			return ( memcmp( m , Matrix.m , 4 * 4 * sizeof( float ) ) != 0 );
		}

		inline float operator[] ( int index ) const
		{
			return m[index];
		}

		inline float& operator[] ( int index )
		{
			return m[index];
		}

	public:
		void SetRotation( const Matrix3f& Rot );
		void SetTranslate( const Vector3f& Trans );
		Vector3f GetTranslate() const;

		Vector3f GetBasisX() const;
		Vector3f GetBasisY() const;
		Vector3f GetBasisZ() const;

		Vector4f	GetRow( int iRow ) const;
		void		SetRow( int iRow , const Vector4f& Vector );
		void		SetRow( int iRow , const Vector3f& Vector );
		Vector4f	GetColumn( int iCol ) const;
		void		SetColumn( int iCol , const Vector4f& Vector );

		Matrix3f	GetMatrix3f();

	public:
		static Matrix4f RotationMatrixXYZ( float fRadiansX , float fRadiansY , float fRadiansZ );
		static Matrix4f RotationMatrixX( float fRadians );
		static Matrix4f RotationMatrixY( float fRadians );
		static Matrix4f RotationMatrixZ( float fRadians );
		static Matrix4f ScaleMatrix( float fScale );
		static Matrix4f ScaleMatrix( const Vector3f& scale );
		static Matrix4f ScaleMatrixXYZ( float fX , float fY , float fZ );
		static Matrix4f TranslationMatrix( float fX , float fY , float fZ );
		static Matrix4f LookAtLHMatrix( Vector3f& eye , Vector3f& at , Vector3f& up );
		static Matrix4f PerspectiveFovLHMatrix( float fovy , float aspect , float zn , float zf );
		static Matrix4f OrthographicLHMatrix( float zn , float zf , float width , float height );

		static Matrix4f Identity();
		static Matrix4f Transpose( Matrix4f& matrix );
		static Matrix4f Inverse( Matrix4f& matrix );

	protected:
		union
		{
			struct
			{
				float m00;
				float m01;
				float m02;
				float m03;

				float m10;
				float m11;
				float m12;
				float m13;

				float m20;
				float m21;
				float m22;
				float m23;

				float m30;
				float m31;
				float m32;
				float m33;
			};

			float m[16];
		};
	};
};
#endif