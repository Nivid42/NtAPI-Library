#include "../includes/NtOP.h"

namespace NtOP {

    HANDLE OpenProcessByPid(DWORD processId, DWORD desiredAccess) {
        // Anti-Detection: Zufällige Verzögerung
        Sleep(500 + (rand() % 2000));

        // Lade ntdll.dll für NtOpenProcess Zugriff
        HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
        if (!ntdll) return INVALID_HANDLE_VALUE;

        // Hole NtOpenProcess Funktionsadresse
        auto NtOpenProcess = (NtOP::Structs::PFN_NTOPENPROCESS)GetProcAddress(ntdll, "NtOpenProcess");
        if (!NtOpenProcess) return INVALID_HANDLE_VALUE;

        // Initialisiere Object Attributes (meist NULL für Prozesse)
        NtOP::Structs::OBJECT_ATTRIBUTES objAttribs = { 0 };
        objAttribs.Length = sizeof(NtOP::Structs::OBJECT_ATTRIBUTES);
        objAttribs.ObjectName = nullptr;  // NULL für einfache Prozess-Öffnung

        // Client ID mit Prozess-ID setzen
        NtOP::Structs::CLIENT_ID clientId = { 0 };
        clientId.UniqueProcess = (HANDLE)(uintptr_t)processId;
        clientId.UniqueThread = nullptr;  // NULL für Prozess (nicht Thread)

        HANDLE processHandle = NULL;

        // NtOpenProcess aufrufen
        NTSTATUS status = NtOpenProcess(
            &processHandle,      // Output: Prozess-Handle
            desiredAccess,       // Gewünschte Zugriffsrechte
            &objAttribs,         // Object Attributes
            &clientId            // Prozess-ID
        );

        // Prüfe ob erfolgreich
        if (!NT_SUCCESS(status)) {
            return INVALID_HANDLE_VALUE;
        }

        return processHandle;
    }

    HANDLE OpenProcessForRead(DWORD processId) {
        // Minimale Rechte für Memory-Read
        return OpenProcessByPid(processId,
            NTOP_PROCESS_VM_READ | NTOP_PROCESS_QUERY_INFORMATION
        );
    }

    HANDLE OpenProcessForWrite(DWORD processId) {
        // Rechte für Memory-Write
        return OpenProcessByPid(processId,
            NTOP_PROCESS_VM_WRITE | NTOP_PROCESS_VM_OPERATION |
            NTOP_PROCESS_VM_READ | NTOP_PROCESS_QUERY_INFORMATION
        );
    }

    HANDLE OpenProcessFullAccess(DWORD processId) {
        // Alle verfügbaren Rechte
        return OpenProcessByPid(processId, NTOP_PROCESS_ALL_ACCESS);
    }

    bool IsValidProcessHandle(HANDLE processHandle) {
        // Prüfe auf ungültige Handle-Werte
        if (processHandle == NULL || processHandle == INVALID_HANDLE_VALUE) {
            return false;
        }

        // Teste Handle mit GetExitCodeProcess
        DWORD exitCode;
        return GetExitCodeProcess(processHandle, &exitCode) != 0;
    }

    bool CloseProcessHandle(HANDLE processHandle) {
        // Prüfe ob Handle gültig ist
        if (!IsValidProcessHandle(processHandle)) {
            return false;
        }

        // Schließe Handle
        return CloseHandle(processHandle) != 0;
    }

    DWORD GetProcessIdFromHandle(HANDLE processHandle) {
        // Prüfe Handle-Gültigkeit
        if (!IsValidProcessHandle(processHandle)) {
            return 0;
        }

        // Verwende GetProcessId API
        return GetProcessId(processHandle);
    }
}