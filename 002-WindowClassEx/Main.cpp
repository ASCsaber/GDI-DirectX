#include <Windows.h>
#include <tchar.h> // _T 头文件
#pragma comment(lib,"winmm.lib")

#pragma region 字符集科普
/*
_T的作用是让你的程序支持Unicode编码，因为Windows使用两种字符集ANSI和UNICODE，
前者就是通常使用的单字节方式，但这种方式处理像中文这样的双字节字符不方便，容易出现半个汉字的情况。
而后者是双字节方式，方便处理双字节字符。
Windows NT的所有与字符有关的函数都提供两种方式的版本，而Windows 9x只支持ANSI方式。
如果你编译一个程序为ANSI方式，_T实际不起任何作用。
而如果编译一个程序为UNICODE方式，则编译器会把"Hello"字符串以UNICODE方式保存。
_T和_L的区别在于，_L不管你是以什么方式编译，一律以UNICODE方式保存。
LPSTR：		32 - bit指针指向一个  字符串，每个字符占1字节
LPTSTR :	32 - bit指针指向一个  字符串，每字符可能占1字节或2字节，取决于Unicode是否定义
LPCSTR :	32 - bit指针指向一个常字符串，每个字符占1字节
LPCTSTR :	32 - bit指针指向一个常字符串，每字符可能占1字节或2字节，取决于Unicode是否定义
L是表示字符串资源为Unicode的。
比如
wchar_tStr[] = L"Hello World!";
这个就是双字节存储字符了。
_T是一个适配的宏～
当#ifdef _UNICODE的时候_T就是L
没有#ifdef _UNICODE的时候_T就是ANSI的。
比如
LPTSTR lpStr = new TCHAR[32];
TCHAR* szBuf = _T("Hello");
以上两句使得无论是在UNICODE编译条件下还是在ANSI编译条件下都是正确编译的。
而且MS推荐你使用相匹配的字符串函数。
比如处理LPTSTR或者LPCTSTR的时候，不要用strlen, 而是要用_tcslen
否则在UNICODE的编译条件下，strlen不能处理wchar_t*的字符串。
T是非常有意思的一个符号（TCHAR、LPCTSTR、LPTSTR、_T()、_TEXT()...），它表示使用一种中间类型，
既不明确表示使用 MBCS，也不明确表示使用 UNICODE。那到底使用哪种字符集 ? 编译的时候才决定
*/
#pragma endregion

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE _T("世界之窗")

HWND hwnd;

void GetMessageCallback();
void PeeckMessageCallback();
LRESULT CALLBACK WindowCallbackProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); // LRESULT long

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR cmdLine, int nCmdShow)
{
	// 窗口设计
	WNDCLASSEX window = { sizeof(WNDCLASSEX) }; // cbSize 设置结构体的字节数大小
	window.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	window.lpfnWndProc = WindowCallbackProcess;
	window.cbClsExtra = 0; // 窗口类附加内存
	window.cbWndExtra = 0; // 窗口附加内存
	window.hInstance = hInstance;
	window.hIcon = (HICON)::LoadImage(hInstance, _T("icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE); //LoadIcon(hInstance, L"icon.ico");
	window.hCursor = LoadCursor(hInstance, IDC_ARROW);
	window.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	window.lpszMenuName = NULL;
	window.lpszClassName = _T("WorldWindow");
	window.hIconSm = NULL;

	// 窗口注册
	if (!RegisterClassEx(&window))
		throw - 1;

	//RECT size;
	//AdjustWindowRect(&size, 0, FALSE);

	//LPRECT size;
	//AdjustWindowRect(size, WS_OVERLAPPEDWINDOW, FALSE);

	// 创建
	hwnd = CreateWindow(_T("WorldWindow"), WINDOW_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	if (!hwnd)
		throw - 1;

	// 显示和更新
	MoveWindow(hwnd, 200, 200, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE); // 移动
	ShowWindow(hwnd, nCmdShow); // 显示
	UpdateWindow(hwnd); // 更新

	//GetMessageCallback();
	PeeckMessageCallback();

	// 注销窗口类
	UnregisterClass(_T("WorldWindow"), window.hInstance);
	return 0;
}

// 阻塞式消息处理
void GetMessageCallback()
{
	// message -> Queue -> GetMessage -> DispatchMessage -> Callback
	//								  -> TranslateMessage -> Queue -> GetMessage -> DispatchMessage -> Callback
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0)) // 不断从消息队列中取出消息 NULL - 表示接收属于调用线程的所有窗口的窗口消息 0, 0 - 表示接收所有消息不过滤
	{
		TranslateMessage(&msg); // 将虚拟键消息转换为字符消息
		DispatchMessage(&msg); // 分发一个消息给窗口程序
	}
}

// 非阻塞式消息处理
void PeeckMessageCallback()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		// 有消息时处理消息，无消息时处理其他绘制
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // 此处窗口句柄最好传递NULL，因为可能某一时间窗口句柄失效了
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 调用更新函数，进行画面的更新
			// 调用渲染函数，进行画面的渲染
		}
	}
}

LRESULT CALLBACK WindowCallbackProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT: // 客户区重绘消息
		// 其他绘制函数
		ValidateRect(hwnd, NULL); // 更新整个客户区域的显示
		break;
	case WM_KEYDOWN: // 键盘按下消息
		if (wParam = VK_ESCAPE)
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY: // 窗口销毁消息
		// 其他COM接口对象释放
		PostQuitMessage(0); // 向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}