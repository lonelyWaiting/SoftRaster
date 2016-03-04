#ifndef Log_h
#define Log_h

#include "PCH.h"

namespace Sand
{
	class Log
	{
	protected:
		Log();

		// ���ַ�������������
		std::wofstream LogFile;

	public:
		static Log& Get();

		void Open();

		void Close();

		void Write( const wchar_t* TextString );

		void Write( std::wstring& TestString );

		void WriteSeparator();
	};
};
#endif