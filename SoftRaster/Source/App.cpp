#include "PCH.h"
#include "App.h"
#include "Color.h"

using namespace Sand;

App Instance;

App::App()
{
	m_pRenderer = nullptr;

	m_iWidth = 800;
	m_iHeight = 600;
}

App::~App()
{

}

bool App::ConfigureEngineComponents()
{
	pWindow->SetSize( m_iWidth , m_iHeight );
	pWindow->SetPosition( 100 , 100 );
	pWindow->SetCaption( GetName() );
	pWindow->Initialize( this );

	pSurface->Init( pWindow->GetHandle() , m_iWidth , m_iHeight );

	m_pRenderer = new Renderer( m_iWidth , m_iHeight , this );
	if ( m_pRenderer == nullptr )
	{
		return false;
	}

	return true;

}

bool App::ShutdownEngineComponents()
{
	return true;
}

void App::Initialize()
{
	m_Entity = new Entity;

	m_Entity->LoadModel( L"thor.obj" );
	m_Entity->SetPosition( Vector3f( 0.0f , -40.0f , 0.0f ) );

	m_pCamera = new Camera;
	m_pCamera->SetPerspective( SAND_PI * 0.25f , ( float )m_iWidth / (float)m_iHeight , 1.0f , 1000.0f );
	m_pCamera->SetViewPosition( Vector3f( 0.0f , 0.0f , -150.0f ) );

}

void App::Update()
{
	m_pRenderer->ClearBackGroundColor( Color( 0 , 0 , 0 ) , CLEAR_DEPTH | CLEAR_COLOR );

	if ( GetAsyncKeyState( 'W' ) & 0x8000 )
	{
		m_pCamera->MoveForward( m_pTimer->DeltaTime() * 6.0f );
	}
	else if ( GetAsyncKeyState( 'S' ) & 0x8000 )
	{
		m_pCamera->MoveBackward( m_pTimer->DeltaTime() * 6.0f );
	}
	else if ( GetAsyncKeyState( 'A' ) & 0x8000 )
	{
		m_pCamera->MoveLeft( m_pTimer->DeltaTime() * 6.0f );
	}
	else if ( GetAsyncKeyState( 'D' ) & 0x8000 )
	{
		m_pCamera->MoveRight( m_pTimer->DeltaTime() * 6.0f );
	}

	// ¼ÓÔØÊý¾Ý
	/*m_pRenderer->LoadToBuffer( m_Entity->GetGeometry() , m_Entity->GetGeometry().m_Texture );

	m_pRenderer->SetCamera( m_pCamera );

	m_pRenderer->TransformToWorldSpace( m_Entity->GetWorldMatrix() );

	m_pRenderer->BackSurfaceCull();

	m_pRenderer->TransformToViewSpace();

	m_pRenderer->TransformToProjectSpace();

	m_pRenderer->TransformToScreenSpace();

	m_pRenderer->Render();*/

	m_pRenderer->Present();
}

void App::Shutdown()
{

}

std::wstring App::GetName()
{
	return std::wstring( L"SoftRaster" );
}

void App::OnMouseDown( WPARAM buttonState , int x , int y )
{
	m_LastMousePos.x = x;
	m_LastMousePos.y = y;

	SetCapture( pWindow->GetHandle() );
}

void App::OnMouseUp( WPARAM buttonState , int x , int y )
{
	ReleaseCapture();
}

void App::OnMouseMove( WPARAM buttonState , int x , int y )
{
	if ( ( buttonState & MK_LBUTTON ) != 0 )
	{
		float dx = ConvertToRadius( 0.25f * static_cast< float >( x - m_LastMousePos.x ) );
		float dy = ConvertToRadius( 0.25f * static_cast< float >( y - m_LastMousePos.y ) );

		m_pCamera->Pitch( dy );
		m_pCamera->RotateY( dx );
	}

	m_LastMousePos.x = x;
	m_LastMousePos.y = y;
}