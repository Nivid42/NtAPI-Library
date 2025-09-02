#include "NtQuerySystemInformation/includes/NtQSI.h"
#include <iostream>

int main() {
    // So benutzen:
    std::wstring target = L"Discord.exe";

    //NtQSI Process ID
    DWORD pid = NtQSI::FindProcessIdByName(target);
    if (pid != 0) {
        std::cout << pid << std::endl;
    }
    else {
        std::cout << "Prozess nicht gefunden." << std::endl;
    }

    //NtOP


    return 0;
}
