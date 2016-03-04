#ifndef FileSystem_h
#define FileSystem_h

#include "PCH.h"

namespace Sand
{
	/*
		用于获取资源目录
	*/
	class FileSystem
	{
	public:
		FileSystem();
		~FileSystem();

		// Log目录
		std::wstring GetLogFolder();

		// 资源目录
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