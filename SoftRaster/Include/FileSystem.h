#ifndef FileSystem_h
#define FileSystem_h

#include "PCH.h"

namespace Sand
{
	/*
		���ڻ�ȡ��ԴĿ¼
	*/
	class FileSystem
	{
	public:
		FileSystem();
		~FileSystem();

		// LogĿ¼
		std::wstring GetLogFolder();

		// ��ԴĿ¼
		std::wstring GetDataFolder();
		std::wstring GetModelFolder();
		std::wstring GetShaderFolder();
		std::wstring GetTextureFolder();

	private:
		static std::wstring sDataFolder;
		static std::wstring sModelSubFolder;
		static std::wstring sShaderSubFolder;
		static std::wstring sTextureSubFolder;
		static std::wstring sLogSubFolder;
	};
};
#endif