#include <Windows.h>
#include <tchar.h> // _T ͷ�ļ�
#pragma comment(lib,"winmm.lib")

#pragma region �ַ�������
/*
_T������������ĳ���֧��Unicode���룬��ΪWindowsʹ�������ַ���ANSI��UNICODE��
ǰ�߾���ͨ��ʹ�õĵ��ֽڷ�ʽ�������ַ�ʽ����������������˫�ֽ��ַ������㣬���׳��ְ�����ֵ������
��������˫�ֽڷ�ʽ�����㴦��˫�ֽ��ַ���
Windows NT���������ַ��йصĺ������ṩ���ַ�ʽ�İ汾����Windows 9xֻ֧��ANSI��ʽ��
��������һ������ΪANSI��ʽ��_Tʵ�ʲ����κ����á�
���������һ������ΪUNICODE��ʽ������������"Hello"�ַ�����UNICODE��ʽ���档
_T��_L���������ڣ�_L����������ʲô��ʽ���룬һ����UNICODE��ʽ���档
LPSTR��		32 - bitָ��ָ��һ��  �ַ�����ÿ���ַ�ռ1�ֽ�
LPTSTR :	32 - bitָ��ָ��һ��  �ַ�����ÿ�ַ�����ռ1�ֽڻ�2�ֽڣ�ȡ����Unicode�Ƿ���
LPCSTR :	32 - bitָ��ָ��һ�����ַ�����ÿ���ַ�ռ1�ֽ�
LPCTSTR :	32 - bitָ��ָ��һ�����ַ�����ÿ�ַ�����ռ1�ֽڻ�2�ֽڣ�ȡ����Unicode�Ƿ���
L�Ǳ�ʾ�ַ�����ԴΪUnicode�ġ�
����
wchar_tStr[] = L"Hello World!";
�������˫�ֽڴ洢�ַ��ˡ�
_T��һ������ĺꡫ
��#ifdef _UNICODE��ʱ��_T����L
û��#ifdef _UNICODE��ʱ��_T����ANSI�ġ�
����
LPTSTR lpStr = new TCHAR[32];
TCHAR* szBuf = _T("Hello");
��������ʹ����������UNICODE���������»�����ANSI���������¶�����ȷ����ġ�
����MS�Ƽ���ʹ����ƥ����ַ���������
���紦��LPTSTR����LPCTSTR��ʱ�򣬲�Ҫ��strlen, ����Ҫ��_tcslen
������UNICODE�ı��������£�strlen���ܴ���wchar_t*���ַ�����
T�Ƿǳ�����˼��һ�����ţ�TCHAR��LPCTSTR��LPTSTR��_T()��_TEXT()...��������ʾʹ��һ���м����ͣ�
�Ȳ���ȷ��ʾʹ�� MBCS��Ҳ����ȷ��ʾʹ�� UNICODE���ǵ���ʹ�������ַ��� ? �����ʱ��ž���
*/
#pragma endregion

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE _T("����֮��")

HWND hwnd;

void GetMessageCallback();
void PeeckMessageCallback();
LRESULT CALLBACK WindowCallbackProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); // LRESULT long

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR cmdLine, int nCmdShow)
{
	// �������
	WNDCLASSEX window = { sizeof(WNDCLASSEX) }; // cbSize ���ýṹ����ֽ�����С
	window.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	window.lpfnWndProc = WindowCallbackProcess;
	window.cbClsExtra = 0; // �����฽���ڴ�
	window.cbWndExtra = 0; // ���ڸ����ڴ�
	window.hInstance = hInstance;
	window.hIcon = (HICON)::LoadImage(hInstance, _T("icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); //LoadIcon(hInstance, L"icon.ico");
	window.hCursor = LoadCursor(hInstance, IDC_ARROW);
	window.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	window.lpszMenuName = NULL;
	window.lpszClassName = _T("WorldWindow");
	window.hIconSm = NULL;

	// ����ע��
	if (!RegisterClassEx(&window))
		throw - 1;

	//RECT size;
	//AdjustWindowRect(&size, 0, FALSE);

	//LPRECT size;
	//AdjustWindowRect(size, WS_OVERLAPPEDWINDOW, FALSE);

	// ����
	hwnd = CreateWindow(_T("WorldWindow"), WINDOW_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	if (!hwnd)
		throw - 1;

	// ��ʾ�͸���
	MoveWindow(hwnd, 200, 200, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE); // �ƶ�
	ShowWindow(hwnd, nCmdShow); // ��ʾ
	UpdateWindow(hwnd); // ����

	//GetMessageCallback();
	PeeckMessageCallback();

	// ע��������
	UnregisterClass(_T("WorldWindow"), window.hInstance);
	return 0;
}

// ����ʽ��Ϣ����
void GetMessageCallback()
{
	// message -> Queue -> GetMessage -> DispatchMessage -> Callback
	//								  -> TranslateMessage -> Queue -> GetMessage -> DispatchMessage -> Callback
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0)) // ���ϴ���Ϣ������ȡ����Ϣ NULL - ��ʾ�������ڵ����̵߳����д��ڵĴ�����Ϣ 0, 0 - ��ʾ����������Ϣ������
	{
		TranslateMessage(&msg); // ���������Ϣת��Ϊ�ַ���Ϣ
		DispatchMessage(&msg); // �ַ�һ����Ϣ�����ڳ���
	}
}

// ������ʽ��Ϣ����
void PeeckMessageCallback()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		// ����Ϣʱ������Ϣ������Ϣʱ������������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // �˴����ھ����ô���NULL����Ϊ����ĳһʱ�䴰�ھ��ʧЧ��
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ���ø��º��������л���ĸ���
			// ������Ⱦ���������л������Ⱦ
		}
	}
}

LRESULT CALLBACK WindowCallbackProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT: // �ͻ����ػ���Ϣ
		// �������ƺ���
		ValidateRect(hwnd, NULL); // ���������ͻ��������ʾ
		break;
	case WM_KEYDOWN: // ���̰�����Ϣ
		if (wParam = VK_ESCAPE)
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY: // ����������Ϣ
		// ����COM�ӿڶ����ͷ�
		PostQuitMessage(0); // ��ϵͳ�����и��߳�����ֹ����������ӦWM_DESTROY��Ϣ
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}