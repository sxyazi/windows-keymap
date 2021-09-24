#include<Windows.h>
#include "utils.h"

void HandleLWinDown() {
	SingleKey(VK_LCONTROL, 0x0);
}

void HandleLWinUp() {
	SingleKey(VK_LCONTROL, KEYEVENTF_KEYUP);
}

void HandleLCtrlDown() {
	SingleKey(VK_LWIN, 0x0);
}

void HandleLCtrlUp() {
	SingleKey(VK_LWIN, KEYEVENTF_KEYUP);
}

void HandleLCtrlTabDown() {
	SingleKey(VK_LCONTROL, KEYEVENTF_KEYUP);
	SingleKey(VK_MENU, 0x0);
}

void HandleLCtrlTabUp() {
	SingleKey(VK_MENU, KEYEVENTF_KEYUP);
}

void HandleLCtrlM() {
	SingleKey(0x4D, KEYEVENTF_KEYUP);
	ReleaseSpecialKeys();

	MinimizeForegroundWindow();
}

void HandleLCtrlQ() {
	SingleKey(0x51, KEYEVENTF_KEYUP);
	ReleaseSpecialKeys();

	DWORD processId = ForegroundProcess();
	TerminateProcessForce(processId);
}

bool HandleLCtrlW() {
	if (!AllowToClose())
		return false;

	SingleKey(0x57, KEYEVENTF_KEYUP);
	ReleaseSpecialKeys();

	CloseForegroundWindow();
}

void HandleLCtrlAltBar() {
	SingleKey(0xDC, KEYEVENTF_KEYUP);
	ReleaseSpecialKeys();

	MessageBox(NULL, (LPCWSTR)L"About to stop service.", (LPCWSTR)L"Keymap", MB_OK | MB_ICONINFORMATION);
	TerminateProcessForce(ConsoleProcess());
	ExitProcess(0);
}
