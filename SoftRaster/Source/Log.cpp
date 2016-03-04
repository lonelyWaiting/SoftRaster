#include "PCH.h"
#include "Log.h"
#include "FileSystem.h"

using namespace Sand;

Log::Log()
{

}

Log& Log::Get()
{
	// ��̬����ֻ����һ��
	static Log log;
	return log;
}

void Log::Open()
{
	FileSystem fs;

	// Log�ļ�·��
	std::wstring FilePath = fs.GetLogFolder() + std::wstring( L"log.txt" );

	// ����֧��
	LogFile.imbue( std::locale( "" , std::locale::all ^ std::locale::numeric ) );

	// ��Log�ļ�
	LogFile.open( FilePath.c_str() );

	// д�����Ϣ
	Write( L"Open Log File" );
}

void Log::Close()
{
	Write( L"close Log File" );

	LogFile.flush();
}

void Log::Write( const wchar_t* TextString )
{
	LogFile << TextString << L'\0' << std::endl;

	LogFile.flush();
}

void Log::Write( std::wstring& TextString )
{
	Log::Write( TextString.c_str() );
}

void Sand::Log::WriteSeparator()
{
	LogFile << L"------------------------------------------------------------------------------\n";

	LogFile.flush();
}
