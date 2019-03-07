/*
DLL injector based on the one found in the opensecuty training course.


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
	char *action;

	info("Target Process ID: %d\n", pID);
	info("DLL Path: %s\n\n", dllPath);

	action = "Opening proccess";

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if (hProcess == NULL) {
		error("%s Failed\n",action);
		return FALSE;
	}
	success("%s Suceeded\n", AccessCheck);


	action = "Allocating memmory in target proccess";
	mRegion = VirtualAllocEx(hProcess, NULL, strlen(dllPath), MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE); 
	
	if (mRegion == NULL) {
		error("%s Failed\n",action);
		return FALSE;
	}
	success("%s Succeeded\n",action);


	action = "Writing to the allocated memory in the target process";
	status = WriteProcessMemory(hProcess, mRegion, (LPCVOID)dllPath, strlen(dllPath), NULL);
	if (!status) {
		error("%s Failed\n",action);
		return FALSE;
	}
	success("%s Succeeded\n",action);


	loadLibrary = GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA");
	action = "Creating a remote thread in the target process";
	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibrary, mRegion, 0, NULL);
	if (hThread == NULL) {
		error("%s Failed\n",action);
		return FALSE;
	}
	success("%s Succeeded\n",action);


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