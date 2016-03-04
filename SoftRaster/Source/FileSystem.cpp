#include "PCH.h"
#include "FileSystem.h"
#include <shlobj.h>

using namespace Sand;

std::wstring FileSystem::sDataFolder = L"../Data/";
std::wstring FileSystem::sModelSubFolder = L"Models/";
std::wstring FileSystem::sShaderSubFolder = L"Shaders/";
std::wstring FileSystem::sTextureSubFolder = L"Textures/";
std::wstring FileSystem::sLogSubFolder = L"Logs/";


FileSystem::FileSystem()
{

}

FileSystem::~FileSystem()
{

}

std::wstring FileSystem::GetDataFolder()
{
	return ( sDataFolder );
}

std::wstring FileSystem::GetLogFolder()
{
	// �ú��������ھ�̬��Ա������ǰ���ã����ֻ��ֱ��д�ɳ���
	return L"../Data/Logs/";
}

std::wstring FileSystem::GetModelFolder()
{
	return ( sDataFolder + sModelSubFolder );
}

std::wstring FileSystem::GetShaderFolder()
{
	return ( sDataFolder + sShaderSubFolder );
}

std::wstring FileSystem::GetTextureFolder()
{
	return ( sDataFolder + sTextureSubFolder );
}