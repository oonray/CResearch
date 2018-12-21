#include <ntddk.h>

NTSTATUS DriverEntry(IN PDRIVER_OBJECT thedriver, IN PUNICODE_STRING theregpath){
    DbgPrint("HEllo World!");
    return STATUS_SUCCESS
}


