#include<iostream>
#include<Windows.h>
#include "keys.h"

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* ks = (KBDLLHOOKSTRUCT*)lParam;

	if (ks->dwExtraInfo == KEY_IDENTIFIER) {
		return CallNextHookEx(NULL, code, wParam, lParam);
	}

	// Left control + M
	if (ks->vkCode == 0x4D && wParam == WM_KEYDOWN && GetKeyState(VK_LCONTROL) & 0x8000) {
		HandleLCtrlM();
		return 1;
	}
	// Left control + Q
	if (ks->vkCode == 0x51 && wParam == WM_KEYDOWN && GetKeyState(VK_LCONTROL) & 0x8000) {
		HandleLCtrlQ();
		return 1;
	}
	// Left control + W
	if (ks->vkCode == 0x57 && wParam == WM_KEYDOWN && GetKeyState(VK_LCONTROL) & 0x8000) {
		HandleLCtrlW();
		return 1;
	}
	// Left (control or win) + Left alt + |
	if (ks->vkCode == 0xDC &&
		(wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) &&
		GetKeyState(VK_MENU) & 0x8000 &&
		GetKeyState(VK_LSHIFT) & 0x8000 && 
		(GetKeyState(VK_LCONTROL) & 0x8000 || GetKeyState(VK_LWIN) & 0x8000)) {

		HandleLCtrlAltBar();

		return 1;
	}
	// Left win
	if (ks->vkCode == VK_LWIN) {
		wParam == WM_KEYDOWN ? HandleLWinDown() : HandleLWinUp();
		return 1;
	}
	// Left control
	if (ks->vkCode == VK_LCONTROL) {
		wParam == WM_KEYDOWN ? HandleLCtrlDown() : HandleLCtrlUp();
		return 1;
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	MSG msg;
	HHOOK g_Hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(g_Hook);

	return 0;
}
