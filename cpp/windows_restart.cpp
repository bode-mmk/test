// RestartWindowsAuto.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include <iostream>
#include <Windows.h>

int main()
{
	auto process = ::GetCurrentProcess();
	HANDLE token = nullptr;
	LUID luid;
	TOKEN_PRIVILEGES token_new, token_old;

	::OpenProcessToken(process,
		TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &token);
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &luid);

	token_new.PrivilegeCount = 1;
	token_new.Privileges[0].Luid = luid;
	token_new.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	DWORD result;
	AdjustTokenPrivileges(token, FALSE, &token_new, sizeof(token_old), &token_old,  &result);

	ExitWindowsEx(EWX_REBOOT, 0);

    return 0;
}

