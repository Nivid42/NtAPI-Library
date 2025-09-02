#pragma once
#include <windows.h>
#include <string>
#include "NtOP_Structs.h"

// NT Status Codes
#define STATUS_SUCCESS 0x00000000L
#define STATUS_ACCESS_DENIED 0xC0000022L
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

namespace NtOP {

    // Öffnet einen Prozess-Handle mit spezifischen Zugriffsrechten
    // Rückgabe: Handle oder INVALID_HANDLE_VALUE bei Fehler
    HANDLE OpenProcessByPid(DWORD processId, DWORD desiredAccess);

    // Convenience-Funktion: Öffnet Prozess mit Read-Zugriff
    HANDLE OpenProcessForRead(DWORD processId);

    // Convenience-Funktion: Öffnet Prozess mit Write-Zugriff  
    HANDLE OpenProcessForWrite(DWORD processId);

    // Convenience-Funktion: Öffnet Prozess mit vollem Zugriff
    HANDLE OpenProcessFullAccess(DWORD processId);

    // Prüft ob ein Handle gültig ist
    bool IsValidProcessHandle(HANDLE processHandle);

    // Schließt einen Prozess-Handle sicher
    bool CloseProcessHandle(HANDLE processHandle);

    // Ermittelt die PID aus einem Handle
    DWORD GetProcessIdFromHandle(HANDLE processHandle);
}