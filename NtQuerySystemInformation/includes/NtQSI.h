#pragma once
#include <windows.h>
#include <string>
#include <memory>
#include "NtQSI_Structs.h"

// Forward-Deklarationen um Header-Abhängigkeiten zu umgehen und Includes zu sparen
//struct SYSTEM_PROCESS_INFORMATION;

// NT Status Codes und Konstanten
#define STATUS_INFO_LENGTH_MISMATCH 0xC0000004L // Fehlercode wenn Puffer zu klein ist
#define SystemProcessInformation 5 // Abfrage-Typ für Systeminformation (5 = Liste aller Prozesse)
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0) // Prüft ob NTSTATUS erfolgreich war oder nicht

namespace NtQSI {
    // Ruft intern ntdll.dll und NtQuerySystemInformation auf, um Prozess zu finden und PID zu bekommen
    // Rückgabe: PID des Prozesses oder 0 wenn nicht gefunden
    DWORD FindProcessIdByName(const std::wstring& processName);
}