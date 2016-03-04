#ifndef Texture_h
#define Texture_h

#include "FreeImage.h"
#include "Color.h"

namespace Sand
{
	class Texture
	{
	public:
		Texture();
		~Texture();

	private:
		void SetDefaults();

	public:
		bool LoadTexture( std::wstring TextureFilename );
		Color GetColorNearest( float s , float t );
		Color GetColorBilinear( float s , float t );
		void Destroy();

	private:
		FIBITMAP* m_pDIB;
		BYTE* m_pBits;

	private:
		int m_iWidth;
		int m_iHeight;
		int m_iPitch;
		int m_iBPP;
	};
};
#endif