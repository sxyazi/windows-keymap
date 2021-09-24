#include<iostream>
#include<Windows.h>
#include "keys.h"

bool altTab = false;


LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* ks = (KBDLLHOOKSTRUCT*)lParam;
	if (ks->dwExtraInfo == KEY_IDENTIFIER) 
		return CallNextHookEx(NULL, code, wParam, lParam);


	short lCtrlDown = GetKeyState(VK_LCONTROL) & 0x8000;
	if (lCtrlDown) {
		// Left ctrl + Tab
		if (ks->vkCode == VK_TAB && !altTab) {
			altTab = true;
			HandleLCtrlTabDown();
			return CallNextHookEx(NULL, code, wParam, lParam);
		}
		// Left control + M
		if (ks->vkCode == 0x4D && wParam == WM_KEYDOWN) {
			HandleLCtrlM();
			return 1;
		}
		// Left control + Q
		if (ks->vkCode == 0x51 && wParam == WM_KEYDOWN) {
			HandleLCtrlQ();
			return 1;
		}
		// Left control + W
		if (ks->vkCode == 0x57 && wParam == WM_KEYDOWN) {
			return HandleLCtrlW() ? 1 : CallNextHookEx(NULL, code, wParam, lParam);
		}
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
		if (!altTab) wParam == WM_KEYDOWN ? HandleLWinDown() : HandleLWinUp();
		if (altTab && (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)) {
			altTab = false;
			HandleLCtrlTabUp();
		}

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
	// ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	MSG msg;
	HHOOK g_Hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(g_Hook);

	return 0;
}
