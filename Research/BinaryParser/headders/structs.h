#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

typedef struct _IMAGE_FILE_HEADER {
  uint32_t  Machine;
  uint32_t  NumberOfSections;
  uint32_t TimeDateStamp;
  uint64_t PointerToSymbolTable;
  uint64_t NumberOfSymbols;
  uint32_t  SizeOfOptionalHeader;
  uint32_t  Characteristics;
} IMAGE_FILE_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
  uint64_t VirtualAddress;
  uint64_t Size;
} IMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_OPTIONAL_HEADER {
  uint32_t             Magic;
  uint8_t              MajorLinkerVersion;
  uint8_t              MinorLinkerVersion;
  uint64_t             SizeOfCode;
  uint64_t             SizeOfInitializedData;
  uint64_t             SizeOfUninitializedData;
  uint64_t             AddressOfEntryPoint;
  uint64_t             BaseOfCode;
  uint64_t             BaseOfData;
  uint64_t             ImageBase;
  uint64_t             SectionAlignment;
  uint64_t             FileAlignment;
  uint32_t             MajorOperatingSystemVersion;
  uint32_t             MinorOperatingSystemVersion;
  uint32_t             MajorImageVersion;
  uint32_t             MinorImageVersion;
  uint32_t             MajorSubsystemVersion;
  uint32_t             MinorSubsystemVersion;
  uint64_t             Win32VersionValue;
  uint64_t             SizeOfImage;
  uint64_t             SizeOfHeaders;
  uint64_t             CheckSum;
  uint32_t             Subsystem;
  uint32_t             DllCharacteristics;
  uint64_t             SizeOfStackReserve;
  uint64_t             SizeOfStackCommit;
  uint64_t             SizeOfHeapReserve;
  uint64_t             SizeOfHeapCommit;
  uint64_t             LoaderFlags;
  uint64_t             NumberOfRvaAndSizes;
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER;

typedef struct _IMAGE_NT_HEADERS {
  uint64_t              Signature;
  IMAGE_FILE_HEADER     FileHeader;
  IMAGE_OPTIONAL_HEADER OptionalHeader;
} IMAGE_NT_HEADERS;


