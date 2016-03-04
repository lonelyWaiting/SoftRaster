#ifndef Surface_h
#define Surface_h

namespace Sand
{
	class Surface
	{
	public:
		Surface();
		~Surface();

		void Init( HWND hwnd , int width , int height );
		
	private:
		void Release();

	private:
		int m_iSurfaceHeight;
		int m_iSurfaceWidth;
		HBITMAP m_hBitmap;
		HBITMAP m_hOldBitmap;

	public:
		HDC m_DeviceContext;
		unsigned char* m_pData;
	};
};
#endif