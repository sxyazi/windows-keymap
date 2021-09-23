#include<Windows.h>
#include<stdio.h>

DWORD currentProcess() {
	DWORD processId;
	if (!GetWindowThreadProcessId(GetForegroundWindow(), &processId))
		return 0;

	return processId;
}

bool processHasExited(HANDLE hProcess) {
	DWORD lpExitCode;
	GetExitCodeProcess(hProcess, &lpExitCode);
	return lpExitCode != 259;
}

bool closeCurrentWindow() {
	PostMessage(GetForegroundWindow(), WM_CLOSE, 0, 0);
	return true;
}

bool minimizeCurrentWindow() {
	HWND hwnd = GetForegroundWindow();
	if (hwnd == NULL) return false;

	return ShowWindow(hwnd, SW_MINIMIZE);
}

bool TerminateCurrentProcess(DWORD processId) {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
	if (hProcess == NULL) return false;

	bool result = false;
	for (int i = 0; i < 5 && !result; i++) {
		TerminateProcess(hProcess, 0);
		result = processHasExited(hProcess);
	}

	CloseHandle(hProcess);
	return result;
}
