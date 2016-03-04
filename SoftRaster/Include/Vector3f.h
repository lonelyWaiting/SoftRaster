#ifndef Vector3f_h
#define Vector3f_h

namespace Sand
{
	class Vector3f
	{
	public:
		inline Vector3f()
			:x( 0 ) , y( 0 ) , z( 0 )
		{

		}

		inline Vector3f( float _x , float _y , float _z )
			: x( _x ) , y( _y ) , z( _z )
		{

		}

		inline Vector3f( const Vector3f& rhs )
			: x( rhs.x ) , y( rhs.y ) , z( rhs.z )
		{

		}

		inline Vector3f( const float rhs[3] )
			: x( rhs[0] ) , y( rhs[1] ) , z( rhs[2] )
		{

		}

	public:
		inline Vector3f operator+ ( const Vector3f& rhs ) const
		{
			return Vector3f( x + rhs.x , y + rhs.y , z + rhs.z );
		}

		inline Vector3f operator- ( const Vector3f& rhs ) const
		{
			return Vector3f( x - rhs.x , y - rhs.y , z - rhs.z );
		}

		inline Vector3f operator* ( const float scale ) const
		{
			return Vector3f( x * scale , y * scale , z * scale );
		}

		inline Vector3f operator* ( const Vector3f& rhs ) const
		{
			return Vector3f( x * rhs.x , y * rhs.y , z * rhs.z );
		}

		inline Vector3f operator- ( ) const
		{
			return Vector3f( -x , -y , -z );
		}

		inline Vector3f& operator+= ( const Vector3f& rhs )
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		inline Vector3f& operator-= ( const Vector3f& rhs )
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		inline Vector3f& operator*= ( const float scale )
		{
			x *= scale;
			y *= scale;
			z *= scale;

			return *this;
		}

		inline Vector3f& operator*= ( const Vector3f& rhs )
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;

			return *this;
		}

		inline friend Vector3f operator* ( const float lhs , const Vector3f& rhs )
		{
			return Vector3f( lhs * rhs.x , lhs * rhs.y , lhs * rhs.z );
		}

		inline Vector3f& operator= ( const Vector3f& rhs )
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;

			return *this;
		}

		inline float operator[] ( int index ) const
		{
			assert( index < 3 );

			return m[index];
		}

		inline float& operator[] ( int index )
		{
			assert( index < 3 );

			return m[index];
		}

	public:
		inline friend Vector3f cross( const Vector3f& lhs , const Vector3f& rhs )
		{
			return Vector3f( lhs.y * rhs.z - lhs.z * rhs.y ,
							 lhs.z * rhs.x - lhs.x * rhs.z ,
							 lhs.x * rhs.y - lhs.y * rhs.x );
		}

		inline friend float dot( const Vector3f& lhs , const Vector3f& rhs )
		{
			return ( lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z );
		}

		inline friend void Clamp( Vector3f& rhs , float Min , float Max )
		{
			if ( rhs.x < Min )
			{
				rhs.x = Min;
			}
			else if ( rhs.x > Max )
			{
				rhs.x = Max;
			}

			if ( rhs.y < Min )
			{
				rhs.y = Min;
			}
			else if ( rhs.y > Max )
			{
				rhs.y = Max;
			}

			if ( rhs.z < Min )
			{
				rhs.z = Min;
			}
			else if ( rhs.z > Max )
			{
				rhs.z = Max;
			}
		}

		inline float Magnitude()
		{
			return sqrtf( x * x + y * y + z * z );
		}

		inline void Normalize()
		{
			float magnitude = Magnitude();

			assert( magnitude > 0.0f );

			float inv = 1.0f / magnitude;

			x *= inv;
			y *= inv;
			z *= inv;
		}

	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};

			struct
			{
				float r;
				float g;
				float b;
			};

			float m[3];
		};
	};
};
#endif