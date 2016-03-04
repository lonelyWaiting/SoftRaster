#ifndef SandString_h
#define SandString_h

#include "PCH.h"

namespace Sand
{
	class SandString
	{
	public:
		static std::string ToAscii( const std::wstring& input );
		static std::wstring ToUnicode( const std::string& input );

	private:
		SandString();
	};

	template<typename T>
	inline std::wstring ToString( const T& value )
	{
		std::wostringstream stream;

		if ( !( stream << value ) )
		{
			return L"";
		}

		return stream.str();
	}
};
#endif