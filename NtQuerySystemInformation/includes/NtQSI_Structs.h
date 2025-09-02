#pragma once
#include <windows.h>

namespace NtQSI {
    namespace Structs {
        // Windows-internes String-Struct für Unicode-Strings (z. B. Prozessnamen), wird konvertiert 
        // Wird im Code zu wstring konvertiert
        struct UNICODE_STRING {
            USHORT Length;
            USHORT MaximumLength;
            PWSTR Buffer;
        };

        struct MY_SYSTEM_PROCESS_INFORMATION {
            ULONG NextEntryOffset;
            ULONG NumberOfThreads;
            BYTE Reserved1[48];
            UNICODE_STRING ImageName;
            LONG BasePriority;
            HANDLE UniqueProcessId; //Für uns am Ende wichtig
            HANDLE InheritedFromUniqueProcessId;
            ULONG HandleCount;
        };

        using PMY_SYSTEM_PROCESS_INFORMATION = MY_SYSTEM_PROCESS_INFORMATION*;

        // Signatur
        using PFN_NTQUERYSYSTEMINFO = NTSTATUS(WINAPI*)(
            ULONG SystemInformationClass,
            PVOID SystemInformation,
            ULONG SystemInformationLength,
            PULONG ReturnLength
            );
    }
}
