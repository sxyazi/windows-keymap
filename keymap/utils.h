#pragma once

void SingleKey(WORD wVk, DWORD dwFlags);
void ReleaseSpecialKeys();

DWORD ConsoleProcess();
DWORD ForegroundProcess();
bool ProcessHasExited(HANDLE hProcess);
bool CloseForegroundWindow();
bool MinimizeForegroundWindow();
bool TerminateProcessForce(DWORD processId);
