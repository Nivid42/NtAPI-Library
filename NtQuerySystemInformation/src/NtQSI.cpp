
#include "../includes/NtQSI.h"

namespace NtQSI {
    DWORD FindProcessIdByName(const std::wstring& targetName) {
        // Anti-Detection: Zufällige Verzögerung um Automatisierung zu verschleiern
        Sleep(1000 + (rand() % 5000));

        // Lade ntdll.dll Modul um Zugriff auf undokumentierte NT APIs zu bekommen
        HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
        if (!ntdll) return 0;

        // Hole Funktionsadresse von NtQuerySystemInformation aus ntdll.dll
        auto NtQuery = (NtQSI::Structs::PFN_NTQUERYSYSTEMINFO)GetProcAddress(ntdll, "NtQuerySystemInformation");
        if (!NtQuery) return 0;

        // Initialisiere Puffer mit Startgröße von 256KB für Prozessliste
        ULONG bufferSize = 0x40000;
        std::unique_ptr<BYTE[]> buffer;
        NTSTATUS status;

        // Schleife um richtige Puffergröße zu ermitteln (System kann mehr Speicher brauchen)
        do {
            buffer = std::make_unique<BYTE[]>(bufferSize);
            status = NtQuery(
                SystemProcessInformation,    // Typ 5: Alle Prozesse abfragen
                buffer.get(),              
                bufferSize,                
                &bufferSize                
            );
            // Falls Puffer zu klein war, verdopple die Größe
            if (status == STATUS_INFO_LENGTH_MISMATCH) {
                bufferSize *= 2;
            }
        } while (status == STATUS_INFO_LENGTH_MISMATCH);

        // Prüfe ob API-Aufruf erfolgreich war, sonst abbrechen
        if (!NT_SUCCESS(status)) return 0;

        // Cast Puffer zu Prozess-Info Struktur für einfachere Verwendung
        NtQSI::Structs::PMY_SYSTEM_PROCESS_INFORMATION processInfo =
            (NtQSI::Structs::PMY_SYSTEM_PROCESS_INFORMATION)buffer.get();

        // Iteriere durch  Liste aller Prozesse im System
        while (processInfo != nullptr) {
            // Prüfe ob Prozess einen gültigen Namen hat (System-Prozess kann NULL sein)
            if (processInfo->ImageName.Buffer != nullptr &&
                processInfo->ImageName.Length > 0) {

                // Konvertiere UNICODE_STRING zu std::wstring für String-Vergleich
                std::wstring processName(
                    processInfo->ImageName.Buffer,
                    processInfo->ImageName.Length / sizeof(WCHAR)  // Length ist in Bytes, nicht Characters
                );

                // Vergleiche aktuellen Prozessnamen mit gesuchtem Namen
                if (processName == targetName) {
                    // Gibt Process ID zurück wenn Process gefunden wurde
                    return (DWORD)(uintptr_t)processInfo->UniqueProcessId;
                }
            }

            // Springe zum nächsten Prozess-Eintrag oder beende falls letzter (Offset = 0)
            if (processInfo->NextEntryOffset == 0) break;
            processInfo = (NtQSI::Structs::PMY_SYSTEM_PROCESS_INFORMATION)(
                (BYTE*)processInfo + processInfo->NextEntryOffset
                );
        }

        // Prozess nicht gefunden, gib 0 zurück
        return 0;
    }
}