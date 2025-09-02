#pragma once
#include <windows.h>

namespace NtOP {
    namespace Structs {
        // Forward-Deklarationen für Windows-Typen
        struct UNICODE_STRING {
            USHORT Length;
            USHORT MaximumLength;
            PWSTR Buffer;
        };

        // NT Object Attributes Struktur für NtOpenProcess
        struct OBJECT_ATTRIBUTES {
            ULONG Length;
            HANDLE RootDirectory;
            UNICODE_STRING* ObjectName;         // Pointer statt PUNICODE_STRING
            ULONG Attributes;
            PVOID SecurityDescriptor;
            PVOID SecurityQualityOfService;
        };

        // Client ID Struktur für Prozess-/Thread-Identifikation
        struct CLIENT_ID {
            HANDLE UniqueProcess;    // Process ID
            HANDLE UniqueThread;     // Thread ID (NULL für Prozess)
        };

        // Funktionszeiger für NtOpenProcess
        using PFN_NTOPENPROCESS = NTSTATUS(WINAPI*)(
            HANDLE* ProcessHandle,              // Output: Handle zum Prozess
            ACCESS_MASK DesiredAccess,          // Gewünschte Zugriffsrechte
            OBJECT_ATTRIBUTES* ObjectAttributes, // Objekt-Attribute (meist NULL)
            CLIENT_ID* ClientId                 // Prozess-ID Struktur
            );
    }
}

// Access Rights Konstanten für Prozesse (außerhalb des namespace)
#define NTOP_PROCESS_TERMINATE 0x0001
#define NTOP_PROCESS_CREATE_THREAD 0x0002
#define NTOP_PROCESS_SET_SESSIONID 0x0004
#define NTOP_PROCESS_VM_OPERATION 0x0008
#define NTOP_PROCESS_VM_READ 0x0010
#define NTOP_PROCESS_VM_WRITE 0x0020
#define NTOP_PROCESS_DUP_HANDLE 0x0040
#define NTOP_PROCESS_CREATE_PROCESS 0x0080
#define NTOP_PROCESS_SET_QUOTA 0x0100
#define NTOP_PROCESS_SET_INFORMATION 0x0200
#define NTOP_PROCESS_QUERY_INFORMATION 0x0400
#define NTOP_PROCESS_SUSPEND_RESUME 0x0800
#define NTOP_PROCESS_QUERY_LIMITED_INFORMATION 0x1000
#define NTOP_PROCESS_ALL_ACCESS 0x1FFFFF
