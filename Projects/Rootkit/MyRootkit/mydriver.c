#include <ntddk.h>

NTSTATUS DriverEntry(IN PDRIVER_OBJECT the_driver,IN PUNICODE_STRING theregistrypath)
{
    DbgPrint("Hello World!");
    return STATUS_SUCCESS;
}