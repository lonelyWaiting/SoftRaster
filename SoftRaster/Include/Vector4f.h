#ifndef Vector4f_h
#define Vector4f_h

#include "Vector3f.h"
#include "Vector2f.h"

namespace Sand
{
	class Vector4f
	{
	public:
		inline Vector4f()
			:x( 0.0f ) , y( 0.0f ) , z( 0.0f ) , w( 0.0f )
		{

		}

		inline Vector4f( float _x , float _y , float _z , float _w )
			: x( _x ) , y( _y ) , z( _z ) , w( _w )
		{

		}

		inline Vector4f( const float rhs[4] )
			: x( rhs[0] ) , y( rhs[1] ) , z( rhs[2] ) , w( rhs[3] )
		{

		}

		inline Vector4f( const Vector3f& rhs )
			: x( rhs.x ) , y( rhs.y ) , z( rhs.z ) , w( 1.0f )
		{

		}

		inline Vector4f( const Vector4f& rhs )
			: x( rhs.x ) , y( rhs.y ) , z( rhs.z ) , w( rhs.w )
		{

		}

	public:
		inline Vector4f operator+ ( const Vector4f& rhs ) const
		{
			return Vector4f( x + rhs.x , y + rhs.y , z + rhs.z , w + rhs.w );
		}

		inline Vector4f operator- ( const Vector4f& rhs ) const
		{
			return Vector4f( x - rhs.x , y - rhs.y , z - rhs.z , w - rhs.w );
		}

		inline Vector4f operator* ( const float scale ) const
		{
			return Vector4f( x * scale , y * scale , z * scale , w * scale );
		}

		inline Vector4f operator* ( const Vector4f& rhs ) const
		{
			return Vector4f( x * rhs.x , y * rhs.y , z * rhs.z , w * rhs.w );
		}

		inline Vector4f operator- ( ) const
		{
			return Vector4f( -x , -y , -z , -w );
		}

		inline Vector4f& operator+= ( const Vector4f& rhs )
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;

			return *this;
		}

		inline Vector4f& operator-= ( const Vector4f& rhs )
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;

			return *this;
		}

		inline Vector4f& operator*= ( const float scale )
		{
			x *= scale;
			y *= scale;
			z *= scale;
			w *= scale;

			return *this;
		}

		inline Vector4f& operator*= ( const Vector4f& rhs )
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;

			return *this;
		}

		inline friend Vector4f operator* ( const float lhs , const Vector4f& rhs )
		{
			return Vector4f( lhs * rhs.x , lhs * rhs.y , lhs * rhs.z , lhs * rhs.w );
		}

		inline Vector4f& operator= ( const Vector4f& rhs )
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;

			return *this;
		}

		inline float operator[] ( int index ) const
		{
			assert( index < 4 );

			return m[index];
		}

		inline float& operator[] ( int index )
		{
			assert( index < 4 );

			return m[index];
		}

	public:
		inline friend void Clamp( Vector4f& rhs )
		{
			if ( rhs.x > 1.0f )
			{
				rhs.x = 1.0f;
			}
			else if ( rhs.x < 0.0f )
			{
				rhs.x = 0.0f;
			}

			if ( rhs.y > 1.0f )
			{
				rhs.y = 1.0f;
			}
			else if ( rhs.y < 0.0f )
			{
				rhs.y = 0.0f;
			}

			if ( rhs.z > 1.0f )
			{
				rhs.z = 1.0f;
			}
			else if ( rhs.z < 0.0f )
			{
				rhs.z = 0.0f;
			}

			if ( rhs.w > 1.0f )
			{
				rhs.w = 1.0f;
			}
			else if ( rhs.w < 0.0f )
			{
				rhs.w = 0.0f;
			}
		}

		inline friend float dot( const Vector4f& lhs , const Vector4f& rhs )
		{
			return ( ( lhs.x * rhs.x ) + ( lhs.y * rhs.y ) + ( lhs.z * rhs.z ) + ( lhs.w * rhs.w ) );
		}

		inline void Normalize()
		{
			float fInvMag = ( 1.0f / Magnitude() );

			x *= fInvMag;
			y *= fInvMag;
			z *= fInvMag;
			w *= fInvMag;
		}

		inline float Magnitude()
		{
			return sqrt( ( x * x ) + ( y * y ) + ( z * z ) + ( w * w ) );
		}

	public:
		Vector3f xyz() const;
		Vector2f xy() const;

	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};

			float m[4];
		};
	};
}
#endif