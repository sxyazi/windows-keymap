#include <string>
#include<stdio.h>
#include<Windows.h>
#include "keys.h"
#include <Psapi.h>
#include <Shlwapi.h>

void SingleKey(WORD wVk, DWORD dwFlags) {
	INPUT inputs[1] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = wVk;
	inputs[0].ki.dwFlags = dwFlags;
	inputs[0].ki.dwExtraInfo = KEY_IDENTIFIER;

	SendInput(1, inputs, sizeof(INPUT));
}

void ReleaseSpecialKeys() {
	INPUT inputs[4] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_MENU;
	inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
	inputs[0].ki.dwExtraInfo = KEY_IDENTIFIER;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_LSHIFT;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
	inputs[1].ki.dwExtraInfo = KEY_IDENTIFIER;

	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = VK_LCONTROL;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
	inputs[2].ki.dwExtraInfo = KEY_IDENTIFIER;

	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = VK_LWIN;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
	inputs[3].ki.dwExtraInfo = KEY_IDENTIFIER;
	SendInput(4, inputs, sizeof(INPUT));
}

DWORD ConsoleProcess() {
	DWORD processId;
	if (!GetWindowThreadProcessId(GetConsoleWindow(), &processId))
		return 0;

	return processId;
}

DWORD ForegroundProcess() {
	DWORD processId;
	if (!GetWindowThreadProcessId(GetForegroundWindow(), &processId))
		return 0;

	return processId;
}

bool ProcessHasExited(HANDLE hProcess) {
	DWORD lpExitCode;
	GetExitCodeProcess(hProcess, &lpExitCode);
	return lpExitCode != 259;
}

bool CloseForegroundWindow() {
	PostMessage(GetForegroundWindow(), WM_CLOSE, 0, 0);
	return true;
}

bool MinimizeForegroundWindow() {
	HWND hwnd = GetForegroundWindow();
	if (hwnd == NULL) return false;

	return ShowWindow(hwnd, SW_MINIMIZE);
}

bool TerminateProcessForce(DWORD processId) {
	bool result = false;
	for (int i = 0; i < 5 && !result; i++) {
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
		if (hProcess == NULL) continue;

		TerminateProcess(hProcess, 0);
		result = ProcessHasExited(hProcess);
		CloseHandle(hProcess);
	}

	return result;
}

bool AllowToClose() {
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, ForegroundProcess());
	if (!hProcess) return true;

	wchar_t path[MAX_PATH];
	if (!GetModuleFileNameExW(hProcess, 0, path, MAX_PATH)) return false;

	wchar_t* filename = PathFindFileNameW(path);

	// Microsoft Edge
	if (wcscmp(filename, L"msedge.exe") == 0) return false;
	// Visual Studio Code
	else if (wcscmp(filename, L"Code.exe") == 0) return false;
	else wprintf(L"Closed process filename: %s\n", filename);

	CloseHandle(hProcess);
}
