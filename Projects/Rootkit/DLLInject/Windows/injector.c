/*

 */

#include <windows.h>
#include <stdio.h>
#include "../../../../CustomGeadders/colors.h"
#include "../../../../CustomGeadders/debug.h"

BOOL Inject(LPSTR dllPath, DWORD pID)
{
	HANDLE hProcess, hThread;
	LPVOID mRegion;
	BOOL status;
	FARPROC loadLibrary;
	
	info("Target Process ID: %d\n", pID);
	info("DLL Path: %s\n\n", dllPath);

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if (hProcess == NULL) {
		error("[failure]\n");
		return FALSE;
	}
	success("[success]\n");


	info("[-] Allocating memory in the target process ... ");
	mRegion = VirtualAllocEx(hProcess, NULL, strlen(dllPath), MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE); 
	
	if (mRegion == NULL) {
		error("[failure]\n");
		return FALSE;
	}
	success("[success]\n");


	info("[-] Writing to the allocated memory in the target process ... ");
	status = WriteProcessMemory(hProcess, mRegion, (LPCVOID)dllPath, strlen(dllPath), NULL);
	if (!status) {
		error("[failure]\n");
		return FALSE;
	}
	success("[success]\n");


	loadLibrary = GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA");
	info("[-] Creating a remote thread in the target process ... ");
	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibrary, mRegion, 0, NULL);
	if (hThread == NULL) {
		error("[failure]\n");
		return FALSE;
	}
	success("[success]\n");


	WaitForSingleObject(hThread, INFINITE);
	VirtualFreeEx(hProcess, mRegion, strlen(dllPath), MEM_RELEASE);
	CloseHandle(hThread);	
	CloseHandle(hProcess);
	return TRUE;
}

int main(int argc, char **argv)
{
	if (argc != 3) {
		printf("Usage: ./%s [DLL path] [Target Process ID]\n", argv[0]);
		exit(1);
	}
	printf("\n");
	if (Inject(argv[1], atoi(argv[2])))
		success("\nInjecting \"%s\" into %s succeeded\n", argv[1], argv[2]);
	else
		error("\nInjecting \"%s\" into %s failed\n", argv[1], argv[2]);
	return 0;
}