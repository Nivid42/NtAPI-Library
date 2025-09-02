#include "NtOpenProcess/includes/NtOP.h"
#include "NtQuerySystemInformation/includes/NtQSI.h"
#include <iostream>

int main() {
    // Searches for PID to OpenProcess
    DWORD pid = NtQSI::FindProcessIdByName(L"target.exe");
    if (pid != 0) {
        // Getting handle from Process
        HANDLE h = NtOP::OpenProcessForWrite(pid);
        // Validate handle
        if (NtOP::IsValidProcessHandle(h)) {
            // Ready for memory operations

            // Close Handle
            NtOP::CloseProcessHandle(h);
        }
    }
    return 0;
}