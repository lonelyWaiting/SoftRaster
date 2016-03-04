#include "PCH.h"

#include "Application.h"
#include "Log.h"

using namespace Sand;

int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPreInstance , LPSTR lpCmdLine , int nShowCmd )
{
	// ��ȡӦ�ó���ʵ������
	Application* m_pApp = Application::Get();
	if ( !m_pApp )
	{
		return -1;
	}

	// ��������
	if ( !m_pApp->ConfigureEngineComponents() )
	{
		// ������ʧ�ܣ��������������
		m_pApp->ShutdownEngineComponents();

		return -1;
	}


	// Ӧ�ó����ʼ��
	m_pApp->Initialize();

	// ��ѭ��
	m_pApp->MessageLoop();

	// �ƺ���
	m_pApp->Shutdown();
	m_pApp->ShutdownEngineComponents();

	return 1;
}