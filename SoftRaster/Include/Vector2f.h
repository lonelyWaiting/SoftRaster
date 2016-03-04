#ifndef Vector2f_h
#define Vector2f_h

namespace Sand
{
	class Vector2f
	{
	public:
		inline Vector2f()
			:x( 0 ) , y( 0 )
		{

		}

		inline Vector2f( const float _x , const float _y )
			: x( _x ) , y( _y )
		{

		}

		inline Vector2f( const Vector2f& rhs )
			: x( rhs.x ) , y( rhs.y )
		{

		}

		inline Vector2f( const float vector[2] )
			: x( vector[0] ) , y( vector[1] )
		{

		}

	public:
		inline Vector2f operator+ ( const Vector2f& rhs ) const
		{
			return Vector2f( x + rhs.x , y + rhs.y );
		}

		inline Vector2f operator- ( const Vector2f& rhs ) const
		{
			return Vector2f( x - rhs.x , y - rhs.y );
		}

		inline Vector2f operator* ( const float scale ) const
		{
			return Vector2f( x * scale , y * scale );
		}

		inline Vector2f operator* ( const Vector2f& rhs ) const
		{
			return Vector2f( x * rhs.x , y * rhs.y );
		}

		inline Vector2f operator- ( ) const
		{
			return Vector2f( -x , -y );
		}

		inline Vector2f& operator+= ( const Vector2f& rhs )
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		inline Vector2f& operator-= ( const Vector2f& rhs )
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		inline Vector2f& operator*= ( const float scale )
		{
			x *= scale;
			y *= scale;

			return *this;
		}

		inline Vector2f& operator*= ( const Vector2f& rhs )
		{
			x *= rhs.x;
			y *= rhs.y;

			return *this;
		}

		inline friend Vector2f operator* ( const float lhs , const Vector2f& rhs )
		{
			return Vector2f( lhs * rhs.x , lhs * rhs.y );
		}

		inline Vector2f& operator= ( const Vector2f& rhs )
		{
			x = rhs.x;
			y = rhs.y;

			return *this;
		}

		inline float operator[] ( int index ) const
		{
			assert( index < 2 );

			return m[index];
		}

		inline float& operator[] ( int index )
		{
			assert( index < 2 );

			return m[index];
		}

	public:
		inline friend void Clamp( Vector2f& rhs )
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
		}

		inline void MakeZero()
		{
			x = 0.0f;
			y = 0.0f;
		}
	public:
		union
		{
			struct
			{
				float x;
				float y;
			};

			float m[2];
		};
	};
}

#endif