#include "PCH.h"
#include "Texture.h"
#include "FileSystem.h"
#include "SandString.h"
#include "Log.h"

using namespace Sand;

Texture::Texture()
{
	SetDefaults();
}

Texture::~Texture()
{

}

void Texture::SetDefaults()
{
	m_pDIB = NULL;
	m_pBits = NULL;

	m_iWidth = 0;
	m_iHeight = 0;
	m_iPitch = 0;
	m_iBPP = 0;
}

bool Texture::LoadTexture( std::wstring TextureFilename )
{
	FileSystem fs;
	std::wstring Path = fs.GetTextureFolder() + TextureFilename;

	std::wstring ErrorText = L"Error Loading File" + TextureFilename + L" -> ";
	
	Destroy();

	FREE_IMAGE_FORMAT FIF = FreeImage_GetFileType( SandString::ToAscii( Path ).c_str() );

	if ( FIF == FIF_UNKNOWN )
	{
		FIF = FreeImage_GetFIFFromFilename( SandString::ToAscii( Path ).c_str() );
	}

	if ( FIF == FIF_UNKNOWN )
	{
		Log::Get().Write( ErrorText + L"FIF is FIF_UNKNOWN" );
		return false;
	}

	if ( FreeImage_FIFSupportsReading( FIF ) )
	{
		m_pDIB = FreeImage_Load( FIF , SandString::ToAscii( Path ).c_str() );
	}

	if ( m_pDIB == NULL )
	{
		Log::Get().Write( ErrorText + L"DIB is NULL" );
		return false;
	}

	m_iWidth = FreeImage_GetWidth( m_pDIB );
	m_iHeight = FreeImage_GetHeight( m_pDIB );
	m_iPitch = FreeImage_GetPitch( m_pDIB );
	m_iBPP = FreeImage_GetBPP( m_pDIB );

	if ( m_iWidth == 0 || m_iHeight == 0 )
	{
		Log::Get().Write( ErrorText + L"Width or Height is 0" );
		Destroy();
		return false;
	}

	if ( m_iBPP != 24 && m_iBPP != 32 )
	{
		Log::Get().Write( ErrorText + L"BPP is not 24 or 32" );
		Destroy();
		return false;
	}

	m_iBPP /= 8;

	m_pBits = FreeImage_GetBits( m_pDIB );

	if ( m_pBits == nullptr )
	{
		Log::Get().Write( ErrorText + L"Bits is NULL" );
		Destroy();
		return false;
	}

	return true;
}

Color Texture::GetColorNearest( float s , float t )
{
	if ( m_pBits != nullptr )
	{
		s -= ( int )s;
		t -= ( int )t;

		// 若s,t为负数时，会执行此语句
		if ( s < 0.0f )	s += 1.0f;
		if ( t < 0.0f )	t += 1.0f;

		int x = ( int )( s * m_iWidth );
		int y = ( int )( t * m_iHeight );

		BYTE* A = m_pBits + m_iPitch * y + m_iBPP * x;
		
		// 按照R , G , B返回
		return Color( A[2] , A[1] , A[0] );
	}

	// 黑色
	return Color( 0 , 0 , 0 );
}

Color Texture::GetColorBilinear( float s , float t )
{
	// 暂时未写
	return Color( 0 , 0 , 0 );
}

void Texture::Destroy()
{
	if ( m_pDIB != NULL )
	{
		FreeImage_Unload( m_pDIB );
	}

	SetDefaults();
}