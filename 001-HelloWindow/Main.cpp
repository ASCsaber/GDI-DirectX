#include <Windows.h>
#pragma comment(lib,"winmm.lib")

// WINAPI -> __stdcall ��ʾһ�ֵ���Լ��
// wWinMain ��������Unicode���͵ı���
// WinMain ��ִ��Unicode��ANSI֮���ת����
// ��������ת�����ܵ���ȱ��һ��Unicode�ַ����е��ַ�����������wWinMain����������ȷ�Ĵ������ݸ�Ӧ�ó����Unicode���͵Ĳ���
//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	PlaySound(L"FirstBlood.wav", NULL, SND_FILENAME | SND_ASYNC);
	MessageBox(NULL, L"HelloWindow", L"WelcomeWindow", MB_OK | MB_ICONWARNING);
	return 0;
}