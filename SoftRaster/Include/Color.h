#ifndef Color_h
#define Color_h

namespace Sand
{
	class Color
	{
	public:
		Color() :
			r( 0 ) , g( 0 ) , b( 0 )
		{

		}

		Color( BYTE _r , BYTE _g , BYTE _b ) :
			r( _r ) , g( _g ) , b( _b )
		{

		}

		Color( const Color& rhs ) :
			r( rhs.r ) , g( rhs.g ) , b( rhs.b )
		{
			
		}

	public:
		inline Color operator+ ( const Color& rhs ) const
		{
			return Color( r + rhs.r < r ? 255 : r + rhs.r , g + rhs.g < g ? 255 : g + rhs.g , b + rhs.b < b ? 255 : b );
		}

		inline Color& operator += ( const Color& rhs )
		{
			r = r + rhs.r < r ? 255 : r + rhs.r;

			g = g + rhs.g < g ? 255 : g + rhs.g;

			b = b + rhs.b < b ? 255 : b + rhs.b;

			return *this;
		}

	public:
		BYTE r;
		BYTE g;
		BYTE b;
	};
};
#endif