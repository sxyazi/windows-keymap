#include<Windows.h>
#include "utils.h"

void singleKey(WORD wVk, DWORD dwFlags) {
	INPUT inputs[1] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = wVk;
	inputs[0].ki.dwFlags = dwFlags;
	inputs[0].ki.dwExtraInfo = 3395;

	SendInput(1, inputs, sizeof(INPUT));
}

void HandleLWinDown() {
	singleKey(VK_LCONTROL, 0x0);
}

void HandleLWinUp() {
	singleKey(VK_LCONTROL, KEYEVENTF_KEYUP);
}

void HandleLCtrlDown() {
	singleKey(VK_LWIN, 0x0);
}

void HandleLCtrlUp() {
	singleKey(VK_LWIN, KEYEVENTF_KEYUP);
}

void HandleLCtrlM() {
	minimizeCurrentWindow();
}

void HandleLCtrlQ() {
	DWORD processId = currentProcess();
	TerminateCurrentProcess(processId);
}

void HandleLCtrlW() {
	closeCurrentWindow();
}
