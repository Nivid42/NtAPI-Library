#include "../includes/NtOP.h"

namespace NtOP {

    HANDLE OpenProcessByPid(DWORD processId, DWORD desiredAccess) {
        // Anti-Detection: Zuf�llige Verz�gerung
        Sleep(500 + (rand() % 2000));

        // Lade ntdll.dll f�r NtOpenProcess Zugriff
        HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
        if (!ntdll) return INVALID_HANDLE_VALUE;

        // Hole NtOpenProcess Funktionsadresse
        auto NtOpenProcess = (NtOP::Structs::PFN_NTOPENPROCESS)GetProcAddress(ntdll, "NtOpenProcess");
        if (!NtOpenProcess) return INVALID_HANDLE_VALUE;

        // Initialisiere Object Attributes (meist NULL f�r Prozesse)
        NtOP::Structs::OBJECT_ATTRIBUTES objAttribs = { 0 };
        objAttribs.Length = sizeof(NtOP::Structs::OBJECT_ATTRIBUTES);
        objAttribs.ObjectName = nullptr;  // NULL f�r einfache Prozess-�ffnung

        // Client ID mit Prozess-ID setzen
        NtOP::Structs::CLIENT_ID clientId = { 0 };
        clientId.UniqueProcess = (HANDLE)(uintptr_t)processId;
        clientId.UniqueThread = nullptr;  // NULL f�r Prozess (nicht Thread)

        HANDLE processHandle = NULL;

        // NtOpenProcess aufrufen
        NTSTATUS status = NtOpenProcess(
            &processHandle,      // Output: Prozess-Handle
            desiredAccess,       // Gew�nschte Zugriffsrechte
            &objAttribs,         // Object Attributes
            &clientId            // Prozess-ID
        );

        // Pr�fe ob erfolgreich
        if (!NT_SUCCESS(status)) {
            return INVALID_HANDLE_VALUE;
        }

        return processHandle;
    }

    HANDLE OpenProcessForRead(DWORD processId) {
        // Minimale Rechte f�r Memory-Read
        return OpenProcessByPid(processId,
            NTOP_PROCESS_VM_READ | NTOP_PROCESS_QUERY_INFORMATION
        );
    }

    HANDLE OpenProcessForWrite(DWORD processId) {
        // Rechte f�r Memory-Write
        return OpenProcessByPid(processId,
            NTOP_PROCESS_VM_WRITE | NTOP_PROCESS_VM_OPERATION |
            NTOP_PROCESS_VM_READ | NTOP_PROCESS_QUERY_INFORMATION
        );
    }

    HANDLE OpenProcessFullAccess(DWORD processId) {
        // Alle verf�gbaren Rechte
        return OpenProcessByPid(processId, NTOP_PROCESS_ALL_ACCESS);
    }

    bool IsValidProcessHandle(HANDLE processHandle) {
        // Pr�fe auf ung�ltige Handle-Werte
        if (processHandle == NULL || processHandle == INVALID_HANDLE_VALUE) {
            return false;
        }

        // Teste Handle mit GetExitCodeProcess
        DWORD exitCode;
        return GetExitCodeProcess(processHandle, &exitCode) != 0;
    }

    bool CloseProcessHandle(HANDLE processHandle) {
        // Pr�fe ob Handle g�ltig ist
        if (!IsValidProcessHandle(processHandle)) {
            return false;
        }

        // Schlie�e Handle
        return CloseHandle(processHandle) != 0;
    }

    DWORD GetProcessIdFromHandle(HANDLE processHandle) {
        // Pr�fe Handle-G�ltigkeit
        if (!IsValidProcessHandle(processHandle)) {
            return 0;
        }

        // Verwende GetProcessId API
        return GetProcessId(processHandle);
    }
}