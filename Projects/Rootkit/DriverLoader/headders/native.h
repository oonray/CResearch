#define SystemLoadAndCallImage 38
#define  STATUS_SUCCESS                    ((NTSTATUS)0x00000000L)
//#define  STATUS_SUCCESS                    ((NTSTATUS)0x00000000L)
typedef  LONG KPRIORITY;
#define  NtGetProcessHeap()		           (Nt_CurrentTeb()->PebBaseAddress->DefaultHeap)
#define  STATUS_INFO_LENGTH_MISMATCH       ((NTSTATUS)0xC0000004L)
#define  NtCurrentThread()		           ((HANDLE) -2)

//========================== NT definitions ==============================
typedef struct _STRING {
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [size_is(MaximumLength), length_is(Length) ]
#endif // MIDL_PASS
    PCHAR Buffer;
} STRING, *PSTRING;

typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;

typedef STRING OEM_STRING;
typedef PSTRING POEM_STRING;

typedef struct _CLIENT_ID{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

#if (_WIN32_WINNT >= 0x0400)
#define EXIT_STACK_SIZE 0x188
#else
#define EXIT_STACK_SIZE 0x190
#endif

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;

typedef long NTSTATUS;

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

typedef struct _SYSTEM_LOAD_AND_CALL_IMAGE
{
UNICODE_STRING ModuleName;
} SYSTEM_LOAD_AND_CALL_IMAGE, *PSYSTEM_LOAD_AND_CALL_IMAGE;

typedef enum {
     AdjustCurrentProcess,
     AdjustCurrentThread
} ADJUST_PRIVILEGE_TYPE; 

typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

typedef enum _SECTION_INHERIT {
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

typedef struct _CURDIR
{
   UNICODE_STRING	DosPath;
   HANDLE			Handle;
} CURDIR, *PCURDIR;

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
	WORD	Flags;
	WORD	Length;
	DWORD	TimeStamp;
	STRING	DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

#define	PROCESS_PARAMETERS_NORMALIZED	1	// pointers in are absolute (not self-relative)

typedef struct _PROCESS_PARAMETERS
{
    ULONG					MaximumLength;
    ULONG					Length;
    ULONG					Flags;				// PROCESS_PARAMETERS_NORMALIZED
    ULONG					DebugFlags;
    HANDLE					ConsoleHandle;
    ULONG					ConsoleFlags;
    HANDLE					StandardInput;
    HANDLE					StandardOutput;
    HANDLE					StandardError;
    CURDIR					CurrentDirectory;
    UNICODE_STRING			DllPath;
    UNICODE_STRING			ImagePathName;
    UNICODE_STRING			CommandLine;
    PWSTR					Environment;
    ULONG					StartingX;
    ULONG					StartingY;
    ULONG					CountX;
    ULONG					CountY;
    ULONG					CountCharsX;
    ULONG					CountCharsY;
    ULONG					FillAttribute;
    ULONG					WindowFlags;
    ULONG					ShowWindowFlags;
    UNICODE_STRING			WindowTitle;
    UNICODE_STRING			Desktop;
    UNICODE_STRING			ShellInfo;
    UNICODE_STRING			RuntimeInfo;
	RTL_DRIVE_LETTER_CURDIR	CurrentDirectores[32];
} PROCESS_PARAMETERS, *PPROCESS_PARAMETERS;
    
typedef struct _PEB {
	ULONG AllocationSize;
	ULONG Unknown1;
	HANDLE ProcessInstance;
	PVOID DllList;
	PPROCESS_PARAMETERS ProcessParameters;
	ULONG Unknown2;
	HANDLE DefaultHeap;

} PEB, *PPEB;


/*typedef struct _SYSTEM_MODULE_INFORMATION
{
	ULONG Reserved[2];
	PVOID Base;
	ULONG Size;
	ULONG Flags;
	USHORT Index;
	USHORT Unknown;
	USHORT LoadCount;
	USHORT ModuleNameOffset;
	CHAR ImageName[256];
} SYSTEM_MODULE_INFORMATION;
*/
typedef struct _TEB {
    struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList;
    PVOID StackBase;
    PVOID StackLimit;
    PVOID SubSystemTib;
    ULONG Version;
    PVOID ArbitraryUserPointer;
    struct _TEB *Self;

	ULONG Unknown1;
	CLIENT_ID ClientID;
	ULONG Unknown2;
	ULONG Unknown3;
	PPEB PebBaseAddress;
	ULONG LastError;
	ULONG Unknown[0x23];
	ULONG Locale;
	ULONG ExitStack[EXIT_STACK_SIZE];

} TEB;
typedef TEB *PTEB;

typedef struct _IO_STATUS_BLOCK
{
	NTSTATUS	Status;
	ULONG		uInformation;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

#define InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->RootDirectory = r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = n;                                \
    (p)->SecurityDescriptor = s;                        \
    (p)->SecurityQualityOfService = NULL;               \
    }
/*
typedef enum {
     AdjustCurrentProcess,
     AdjustCurrentThread
} ADJUST_PRIVILEGE_TYPE; 
*/
typedef struct _INITIAL_TEB
{
    PVOID PreviousStackBase;
    PVOID PreviousStackLimit;
    PVOID StackBase;
    PVOID StackLimit;
    PVOID AllocatedStackBase;
} INITIAL_TEB, *PINITIAL_TEB;

typedef struct _SYSTEM_MODULE
{
    ULONG	Reserved[2];
    ULONG	Base;
    ULONG	Size;
    ULONG	Flags;
    USHORT	Index;
    USHORT	Unknown;
    USHORT	LoadCount;
    USHORT	ModuleNameOffset;
    CHAR	ImageName[256];
} SYSTEM_MODULE, *PSYSTEM_MODULE;

typedef struct _SYSTEM_MODULE_INFORMATION
{
	ULONG			uCount;
	SYSTEM_MODULE	aSM[0];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS {

SystemBasicInformation, 
SystemProcessorInformation, 
SystemPerformanceInformation, 
SystemTimeOfDayInformation, 
SystemPathInformation, 
SystemProcessInformation, 
SystemCallCountInformation, 
SystemDeviceInformation, 
SystemProcessorPerformanceInformation, 
SystemFlagsInformation, 
SystemCallTimeInformation, 
//SystemModuleInformation, 
SystemLocksInformation, 
SystemStackTraceInformation, 
SystemPagedPoolInformation, 
SystemNonPagedPoolInformation, 
SystemHandleInformation, 
SystemObjectInformation, 
SystemPageFileInformation, 
SystemVdmInstemulInformation, 
SystemVdmBopInformation, 
SystemFileCacheInformation, 
SystemPoolTagInformation, 
SystemInterruptInformation, 
SystemDpcBehaviorInformation, 
SystemFullMemoryInformation, 
SystemLoadGdiDriverInformation, 
SystemUnloadGdiDriverInformation, 
SystemTimeAdjustmentInformation, 
SystemSummaryMemoryInformation, 
SystemNextEventIdInformation, 
SystemEventIdsInformation, 
SystemCrashDumpInformation, 
SystemExceptionInformation, 
SystemCrashDumpStateInformation, 
SystemKernelDebuggerInformation, 
SystemContextSwitchInformation, 
SystemRegistryQuotaInformation, 
SystemExtendServiceTableInformation, 
SystemPrioritySeperation, 
SystemPlugPlayBusInformation, 
SystemDockInformation, 
//SystemPowerInformation, 
SystemProcessorSpeedInformation, 
SystemCurrentTimeZoneInformation, 
SystemLookasideInformation

} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;

typedef struct _VM_COUNTERS
{
	ULONG PeakVirtualSize;              
	ULONG VirtualSize;               
	ULONG PageFaultCount;            
	ULONG PeakWorkingSetSize;            
	ULONG WorkingSetSize;             
	ULONG QuotaPeakPagedPoolUsage;     
	ULONG QuotaPagedPoolUsage;          
	ULONG QuotaPeakNonPagedPoolUsage;    
	ULONG QuotaNonPagedPoolUsage;      
	ULONG PagefileUsage;           
	ULONG PeakPagefileUsage;  
}VM_COUNTERS,*PVM_COUNTERS;

typedef enum _KTHREAD_STATE {
    Initialized,
    Ready,
    Running,
    Standby,
    Terminated, 
    Waiting,
    Transition,
    DeferredReady,
} THREAD_STATE, *PTHREAD_STATE;

typedef enum
{
  Executive,
  FreePage,
  PageIn,
  PoolAllocation,
  DelayExecution,
  Suspended,
  UserRequest,
  WrExecutive,
  WrFreePage,
  WrPageIn,
  WrPoolAllocation,
  WrDelayExecution,
  WrSuspended,
  WrUserRequest,
  WrEventPair,
  WrQueue,
  WrLpcReceive,
  WrLpcReply,
  WrVirtualMemory,
  WrPageOut,
  WrRendezvous,
  Spare2,
  Spare3,
  Spare4,
  Spare5,
  Spare6,
  WrKernel,
  MaximumWaitReason
} KWAIT_REASON;

typedef struct _SYSTEM_THREADS
{
	LARGE_INTEGER KernelTime;       
	LARGE_INTEGER UserTime;            
	LARGE_INTEGER CreateTime;       
	ULONG         WaitTime;         
	PVOID         StartAddress;      
	CLIENT_ID     ClientId;             
	KPRIORITY     Priority;        
	KPRIORITY     BasePriority;     
	ULONG         ContextSwitchCount;    
	THREAD_STATE  State;            
	KWAIT_REASON  WaitReason;    
}SYSTEM_THREADS,*PSYSTEM_THREADS;

typedef struct _SYSTEM_PROCESSES {
	ULONG  NextEntryDelta;
	ULONG  ThreadCount;
	ULONG  Reserved1[6];
	LARGE_INTEGER  CreateTime;
	LARGE_INTEGER  UserTime;
	LARGE_INTEGER  KernelTime;
	UNICODE_STRING  ProcessName;
	KPRIORITY  BasePriority;
	HANDLE  ProcessId;
	HANDLE  InheritedFromProcessId;
	ULONG  HandleCount;
	ULONG  Reserved2[2];
	VM_COUNTERS  VmCounters;
	IO_COUNTERS  IoCounters;
	SYSTEM_THREADS  Threads[1];
} SYSTEM_PROCESSES, *PSYSTEM_PROCESSES;


typedef enum _KEY_VALUE_INFORMATION_CLASS {
  KeyValueBasicInformation,
  KeyValueFullInformation,
  KeyValuePartialInformation
} KEY_VALUE_INFORMATION_CLASS;

typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
    ULONG   TitleIndex;
    ULONG   Type;
    ULONG   DataLength;
    UCHAR   Data[1];
} KEY_VALUE_PARTIAL_INFORMATION,
  *PKEY_VALUE_PARTIAL_INFORMATION;

typedef NTSTATUS(NTAPI * PRTL_HEAP_COMMIT_ROUTINE)(IN PVOID Base,
		IN OUT PVOID *CommitAddress,IN OUT PSIZE_T CommitSize);

typedef struct _RTL_HEAP_PARAMETERS {
    ULONG Length;
    SIZE_T SegmentReserve;
    SIZE_T SegmentCommit;
    SIZE_T DeCommitFreeBlockThreshold;
    SIZE_T DeCommitTotalFreeThreshold;
    SIZE_T MaximumAllocationSize;
    SIZE_T VirtualMemoryThreshold;
    SIZE_T InitialCommit;
    SIZE_T InitialReserve;
    PRTL_HEAP_COMMIT_ROUTINE CommitRoutine;
    SIZE_T Reserved[ 2 ];
} RTL_HEAP_PARAMETERS, *PRTL_HEAP_PARAMETERS;

typedef struct tagPROCENTRY32 {
  DWORD     dwSize;
  DWORD     cntUsage;
  DWORD     th32ProcessID;
  ULONG_PTR th32DefaultHeapID;
  DWORD     th32ModuleID;
  DWORD     cntThreads;
  DWORD     th32ParentProcessID;
  LONG      pcPriClassBase;
  DWORD     dwFlags;
  TCHAR     szExeFile[MAX_PATH];
} PROCENTRY32, *PPROCENTRY32;

typedef enum _MEMORY_INFORMATION_CLASS {

MemoryBasicInformation

} MEMORY_INFORMATION_CLASS, *PMEMORY_INFORMATION_CLASS;

typedef struct {
	ULONG    	Length;
	ULONG    	Unknown[11];
} RTL_HEAP_DEFINITION, *PRTL_HEAP_DEFINITION;


PTEB (NTAPI *Nt_CurrentTeb)(VOID);
NTSTATUS (NTAPI *NtLoadDriver)( IN PUNICODE_STRING DriverServiceName );
NTSTATUS (NTAPI *ZwSetSystemInformation)(DWORD, PVOID, ULONG);
VOID (NTAPI *RtlInitUnicodeString)(PUNICODE_STRING DestinationString,PCWSTR SourceString);
NTSTATUS (NTAPI *NtClose)(HANDLE ObjectHandle);
LONG (__stdcall *RtlAdjustPrivilege)(int,BOOL,BOOL,BOOL *);
NTSTATUS (NTAPI *NtUnloadDriver)( IN PUNICODE_STRING DriverServiceName );
NTSTATUS (NTAPI *RtlAllocateHeap)(PVOID HeapHandle,ULONG Flags,ULONG Size);
NTSTATUS (NTAPI *NtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, 
         DWORD SystemInformationLength, PDWORD ReturnLength);
NTSTATUS (NTAPI *RtlFreeHeap)(PVOID HeapHandle,ULONG Flags,PVOID MemoryPointer); 
NTSTATUS (NTAPI *NtOpenProcess)(PHANDLE ProcessHandle, ACCESS_MASK AccessMask, 
                POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId );
NTSTATUS (NTAPI *NtAllocateVirtualMemory)(IN HANDLE ProcessHandle, IN OUT PVOID *BaseAddress,IN ULONG ZeroBits,
						IN OUT PULONG RegionSize,IN ULONG AllocationType, IN ULONG Protect);
LPVOID NtVirtualAlloc(IN HANDLE hProcess,IN LPVOID  lpAddress,IN SIZE_T dwSize,
		                     IN DWORD  	flAllocationType, IN DWORD  flProtect) {
     NTSTATUS Status;
     Status = NtAllocateVirtualMemory(hProcess,(PVOID *)&lpAddress,0,&dwSize,flAllocationType,flProtect);
     if (!NT_SUCCESS(Status))return NULL;
     return lpAddress;
}
NTSTATUS (NTAPI *NtWriteVirtualMemory)(IN HANDLE ProcessHandle, IN PVOID BaseAddress, IN PVOID Buffer,
						IN ULONG NumberOfBytesToWrite, OUT PULONG  NumberOfBytesWritten OPTIONAL);
NTSTATUS (NTAPI *RtlCreateUserThread)( IN HANDLE ProcessHandle,IN PSECURITY_DESCRIPTOR SecurityDescriptor OPTIONAL,
						IN BOOLEAN CreateSuspended,IN ULONG StackZeroBits OPTIONAL,
						IN SIZE_T StackReserve OPTIONAL,IN SIZE_T StackCommit OPTIONAL,
						IN LPTHREAD_START_ROUTINE StartAddress,IN PVOID Parameter  OPTIONAL,
						OUT PHANDLE ThreadHandle OPTIONAL,OUT PCLIENT_ID ClientId OPTIONAL );
//=================== end of NT definitions ===============================

HANDLE KeGetPID(WCHAR *pstrProcessName){
        NTSTATUS Status; //HANDLE Procheap;
        SIZE_T cbBuffer = 0x8000;
        PVOID pBuffer = NULL;
        HANDLE hResult = NULL;
		PULONG dwId;
		PSYSTEM_PROCESSES pProcesses;
		RTL_HEAP_DEFINITION  heapParams;
		heapParams.Length = sizeof( RTL_HEAP_PARAMETERS );

        do{
            pBuffer = (void *)RtlAllocateHeap(NtGetProcessHeap(), 0, cbBuffer); if (pBuffer == NULL)return 0;
            Status = NtQuerySystemInformation(SystemProcessInformation,pBuffer, cbBuffer, NULL);
            if (Status == STATUS_INFO_LENGTH_MISMATCH){ RtlFreeHeap(NtGetProcessHeap()	, 0, pBuffer); cbBuffer *= 2;
            }else if (!NT_SUCCESS(Status)){ RtlFreeHeap(NtGetProcessHeap(), 0, pBuffer); return 0; }
        }
        while (Status == STATUS_INFO_LENGTH_MISMATCH);
        pProcesses = (PSYSTEM_PROCESSES)pBuffer;

        for (;;){
            WCHAR *pszProcessName = pProcesses->ProcessName.Buffer;
            if (pszProcessName == NULL)pszProcessName = L"Idle";
            if(wcscmp(pszProcessName, pstrProcessName) == 0){
				dwId = (ULONG *)pProcesses->ProcessId;
                break;
            }

            if (pProcesses->NextEntryDelta == 0)break;
            pProcesses = (PSYSTEM_PROCESSES)(((BYTE *)pProcesses)+ pProcesses->NextEntryDelta);
        }
RtlFreeHeap(NtGetProcessHeap()	, 0, pBuffer);
return dwId;
}

