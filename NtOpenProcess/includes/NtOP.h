#pragma once
#include <windows.h>
#include <string>
#include "NtOP_Structs.h"

// NT Status Codes
#define STATUS_SUCCESS 0x00000000L
#define STATUS_ACCESS_DENIED 0xC0000022L
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

namespace NtOP {

    // �ffnet einen Prozess-Handle mit spezifischen Zugriffsrechten
    // R�ckgabe: Handle oder INVALID_HANDLE_VALUE bei Fehler
    HANDLE OpenProcessByPid(DWORD processId, DWORD desiredAccess);

    // Convenience-Funktion: �ffnet Prozess mit Read-Zugriff
    HANDLE OpenProcessForRead(DWORD processId);

    // Convenience-Funktion: �ffnet Prozess mit Write-Zugriff  
    HANDLE OpenProcessForWrite(DWORD processId);

    // Convenience-Funktion: �ffnet Prozess mit vollem Zugriff
    HANDLE OpenProcessFullAccess(DWORD processId);

    // Pr�ft ob ein Handle g�ltig ist
    bool IsValidProcessHandle(HANDLE processHandle);

    // Schlie�t einen Prozess-Handle sicher
    bool CloseProcessHandle(HANDLE processHandle);

    // Ermittelt die PID aus einem Handle
    DWORD GetProcessIdFromHandle(HANDLE processHandle);
}