#include<iostream>
#include<Windows.h>
#include "keys.h"

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	/*
		typedef struct tagKBDLLHOOKSTRUCT {
			DWORD     vkCode;		// 按键代号
			DWORD     scanCode;		// 硬件扫描代号，同 vkCode 也可以作为按键的代号。
			DWORD     flags;		// 事件类型，一般按键按下为 0 抬起为 128。
			DWORD     time;			// 消息时间戳
			ULONG_PTR dwExtraInfo;	// 消息附加信息，一般为 0。
		}KBDLLHOOKSTRUCT,*LPKBDLLHOOKSTRUCT,*PKBDLLHOOKSTRUCT;
	*/

	KBDLLHOOKSTRUCT* ks = (KBDLLHOOKSTRUCT*) lParam;

	if (wParam == WM_KEYDOWN)
	{
		// printf("key:%d, extra:%d down\n", ks->vkCode, ks->dwExtraInfo);
	}
	else if (wParam == WM_KEYUP)
	{
		// printf("key:%d, extra:%d up\n", ks->vkCode, ks->dwExtraInfo);
	}

	if (ks->dwExtraInfo == 3395) 
	{
		return CallNextHookEx(NULL, code, wParam, lParam);
	}

	// Left win key
	if (ks->vkCode == VK_LWIN) 
	{
		wParam == WM_KEYDOWN ? HandleLWinDown() : HandleLWinUp();
		return 1;
	}
	// Left control key
	if (ks->vkCode == VK_LCONTROL)
	{
		wParam == WM_KEYDOWN ? HandleLCtrlDown() : HandleLCtrlUp();
		return 1;
	}
	// Left control + M key
	if (ks->vkCode == 0x4D && wParam == WM_KEYDOWN && GetKeyState(VK_LCONTROL) & 0x8000)
	{
		HandleLCtrlM();
		return 1;
	}
	// Left control + Q key
	if (ks->vkCode == 0x51 && wParam == WM_KEYDOWN && GetKeyState(VK_LCONTROL) & 0x8000)
	{
		HandleLCtrlQ();
		return 1;
	}
	// Left control + W key
	if (ks->vkCode == 0x57 && wParam == WM_KEYDOWN && GetKeyState(VK_LCONTROL) & 0x8000)
	{
		HandleLCtrlW();
		return 1;
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}

int main()
{
	HINSTANCE hInst = GetModuleHandle(NULL);
	HHOOK g_Hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInst, 0);

	// 消息循环是必须的，Windows直接在你自己的进程中调用你的hook回调.要做这个工作,
	//需要一个消息循环.没有其他机制可以让您的主线程进行回调,
	//回调只能在您调用Get / PeekMessage()以使Windows可以控制时发生.

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(g_Hook);

	return 0;
}
