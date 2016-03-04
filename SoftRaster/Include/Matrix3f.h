#ifndef Matrix3f_h
#define Matrix3f_h

#include "Vector3f.h"

namespace Sand
{
	class Matrix3f
	{
	public:
		inline Matrix3f()
			:	m00( 1 ) , m01( 0 ) , m02( 0 ) ,
				m10( 0 ) , m11( 1 ) , m12( 0 ) ,
				m20( 0 ) , m21( 0 ) , m22( 1 )
		{

		}

		inline Matrix3f( const float arr[3][3] )
		{
			memcpy( m , arr , 9 * sizeof( float ) );
		}

		inline Matrix3f( const float arr[9] )
		{
			memcpy( this->m , arr , 9 * sizeof( float ) );
		}

		inline Matrix3f( float _m00 , float _m01 , float _m02 ,
						 float _m10 , float _m11 , float _m12 ,
						 float _m20 , float _m21 , float _m22 )
		{
			m00 = _m00;
			m01 = _m01;
			m02 = _m02;

			m10 = _m10;
			m11 = _m11;
			m12 = _m12;

			m20 = _m20;
			m21 = _m21;
			m22 = _m22;
		}

		inline Matrix3f( const Matrix3f& matrix )
		{
			memcpy( this->m , matrix.m , 9 * sizeof( float ) );
		}

	public:
		inline Matrix3f& operator= ( const Matrix3f& rhs )
		{
			memcpy( this->m , rhs.m , 9 * sizeof( float ) );

			return *this;
		}

		Matrix3f operator* ( const Matrix3f& rhs ) const
		{
			return Matrix3f( m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 ,
							 m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 ,
							 m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 ,
							 m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 ,
							 m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 ,
							 m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 ,
							 m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 ,
							 m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 ,
							 m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 );
		}

		Matrix3f& operator*= ( const Matrix3f& rhs )
		{
			Matrix3f temp = *this;

			m00 = temp.m00 * rhs.m00 + temp.m01 * rhs.m10 + temp.m02 * rhs.m20;
			m01 = temp.m00 * rhs.m01 + temp.m01 * rhs.m11 + temp.m02 * rhs.m21;
			m02 = temp.m00 * rhs.m02 + temp.m01 * rhs.m12 + temp.m02 * rhs.m22;
			m10 = temp.m10 * rhs.m00 + temp.m11 * rhs.m10 + temp.m12 * rhs.m20;
			m11 = temp.m10 * rhs.m01 + temp.m11 * rhs.m11 + temp.m12 * rhs.m21;
			m12 = temp.m10 * rhs.m02 + temp.m11 * rhs.m12 + temp.m12 * rhs.m22;
			m20 = temp.m20 * rhs.m00 + temp.m21 * rhs.m10 + temp.m22 * rhs.m20;
			m21 = temp.m20 * rhs.m01 + temp.m21 * rhs.m11 + temp.m22 * rhs.m21;
			m22 = temp.m20 * rhs.m02 + temp.m21 * rhs.m12 + temp.m22 * rhs.m22;

			return *this;
		}

		inline friend Vector3f operator* ( const Vector3f& lhs , const Matrix3f& rhs )
		{
			return Vector3f( lhs.x * rhs.m00 + lhs.y * rhs.m10 + lhs.z * rhs.m20 ,
							 lhs.x * rhs.m01 + lhs.y * rhs.m11 + lhs.z * rhs.m21 ,
							 lhs.x * rhs.m02 + lhs.y * rhs.m12 + lhs.z * rhs.m22 );
		}

		inline bool operator== ( const Matrix3f& Matrix ) const
		{
			return ( memcmp( m , Matrix.m , 3 * 3 * sizeof( float ) ) == 0 );
		}

		inline bool operator!= ( const Matrix3f& Matrix ) const
		{
			return ( memcmp( m , Matrix.m , 3 * 3 * sizeof( float ) ) != 0 );
		}

		float operator[] ( int index ) const
		{
			return m[index];
		}

		float& operator[] ( int index )
		{
			return m[index];
		}

	public:
		static Matrix3f RotationX( float fRadians );
		static Matrix3f RotationY( float fRadians );
		static Matrix3f RotationZ( float fRadians );

		static Matrix3f Rotation( Vector3f& xyz );
		static Matrix3f RotationZYX( Vector3f& xyz );
		static Matrix3f RotateAxis( Vector3f& Axis , float fRadians );

		static Matrix3f Identity();
		static Matrix3f Transpose( Matrix3f& matrix );

	public:
		void SetRow( int iRow , const Vector3f& Vector );
		Vector3f GetRow( int iRow ) const;
		void SetColumn( int iCol , const Vector3f& Vector );
		Vector3f GetColumn( int iCol ) const;

		void Orthonormalize();

	protected:
		union
		{
			struct
			{
				float m00;
				float m01;
				float m02;

				float m10;
				float m11;
				float m12;

				float m20;
				float m21;
				float m22;
			};

			float m[9];
		};
	};
};
#endif