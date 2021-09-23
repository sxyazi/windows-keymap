#pragma once

DWORD currentProcess();
bool processHasExited(HANDLE hProcess);
bool closeCurrentWindow();
bool minimizeCurrentWindow();
bool TerminateCurrentProcess(DWORD processId);
