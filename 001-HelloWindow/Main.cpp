#include <Windows.h>
#pragma comment(lib,"winmm.lib")

// WINAPI -> __stdcall 表示一种调用约定
// wWinMain 用来处理Unicode类型的变量
// WinMain 会执行Unicode和ANSI之间的转换。
// 而这样的转换可能导致缺少一个Unicode字符串中的字符。所以运用wWinMain能让我们正确的处理被传递给应用程序的Unicode类型的参数
//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	PlaySound(L"FirstBlood.wav", NULL, SND_FILENAME | SND_ASYNC);
	MessageBox(NULL, L"HelloWindow", L"WelcomeWindow", MB_OK | MB_ICONWARNING);
	return 0;
}