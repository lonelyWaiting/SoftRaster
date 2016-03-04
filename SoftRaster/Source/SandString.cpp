#include "PCH.h"
#include "SandString.h"
#include <codecvt>
#include <locale>

using namespace Sand;

SandString::SandString()
{

}

std::string SandString::ToAscii( const std::wstring& input )
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t> , wchar_t>().to_bytes( input );
}

std::wstring SandString::ToUnicode( const std::string& input )
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t> , wchar_t>().from_bytes( input );
}