# NtOpenProcess Module

Advanced process handle management using the native `NtOpenProcess` API with granular access control.

## Features

- **Direct NT API Access**: Bypasses Win32 layer for better stealth characteristics
- **Granular Permissions**: Specify exact access rights required for operations
- **Handle Validation**: Built-in verification of handle integrity and usability
- **Anti-Detection**: Random delays and indirect API loading mechanisms
- **Memory Efficient**: Minimal overhead with automatic cleanup utilities

## Requirements

- Windows 10/11 (any edition)
- Visual Studio 2019+ or compatible C++17 compiler
- Windows SDK
- Administrator privileges recommended for system processes

## Quick Start

### Basic Usage
```cpp
#include "../NtQuerySystemInformation/includes/NtQSI.h"
#include "includes/NtOP.h"
#include <iostream>

int main() {
    DWORD pid = NtQSI::FindProcessIdByName(L"target.exe");
    if (pid != 0) {
        HANDLE h = NtOP::OpenProcessForWrite(pid);
        if (NtOP::IsValidProcessHandle(h)) {
            // Ready for memory operations
            NtOP::CloseProcessHandle(h);
        }
    }
    return 0;
}
```

### Integration into Existing Project

```cpp
// Add to your includes
#include "path/to/NtOpenProcess/includes/NtOP.h"

// Add to your build
// Visual Studio: Add NtOpenProcess/src/NtOP.cpp to Source Files
```

## API Reference

### `OpenProcessByPid(DWORD processId, DWORD desiredAccess)`

Opens a process handle with specified access rights using native NT API.

#### Parameters
- `processId` (DWORD): Target process identifier
- `desiredAccess` (DWORD): Combination of access right flags (use NTOP_* constants)

#### Return Value
- `HANDLE`: Valid process handle if successful, or `INVALID_HANDLE_VALUE` on failure

### `OpenProcessForRead(DWORD processId)`

Convenience function for read-only process access.

#### Parameters
- `processId` (DWORD): Target process identifier

#### Return Value
- `HANDLE`: Process handle with read permissions, or `INVALID_HANDLE_VALUE` on failure

### `OpenProcessForWrite(DWORD processId)`

Convenience function for memory modification access.

#### Parameters
- `processId` (DWORD): Target process identifier

#### Return Value
- `HANDLE`: Process handle with write permissions, or `INVALID_HANDLE_VALUE` on failure

### `IsValidProcessHandle(HANDLE processHandle)`

Validates process handle integrity and accessibility.

#### Parameters
- `processHandle` (HANDLE): Handle to validate

#### Return Value
- `bool`: `true` if handle is valid and usable, `false` otherwise

## Build Instructions

### Visual Studio

1. **Add Source File**:
   ```
   Solution Explorer → Source Files → Add → Existing Item
   Select: src/NtOP.cpp
   ```

2. **Add Headers**:
   ```
   Solution Explorer → Header Files → Add → Existing Item
   Select: includes/NtOP.h and includes/NtOP_Structs.h
   ```

3. **Include in Code**:
   ```cpp
   #include "NtOpenProcess/includes/NtOP.h"
   ```

## Advanced Usage

### Error Handling

```cpp
HANDLE hProcess = NtOP::OpenProcessForRead(targetPid);
if (hProcess == INVALID_HANDLE_VALUE) {
    std::cerr << "Handle acquisition failed - possible causes:" << std::endl;
    std::cerr << "- Process does not exist" << std::endl;
    std::cerr << "- Insufficient privileges" << std::endl;
    std::cerr << "- Process protection active" << std::endl;
    return -1;
}

// Validate before use
if (!NtOP::IsValidProcessHandle(hProcess)) {
    std::cerr << "Handle validation failed" << std::endl;
    return -1;
}

// Use handle for operations
NtOP::CloseProcessHandle(hProcess);
```

### Custom Access Rights

```cpp
// Combine specific access rights
DWORD customAccess = NTOP_PROCESS_VM_READ | 
                     NTOP_PROCESS_QUERY_INFORMATION |
                     NTOP_PROCESS_VM_OPERATION;

HANDLE hProcess = NtOP::OpenProcessByPid(targetPid, customAccess);
```

## Security Considerations

### Privileges Required
- **Standard User**: Can access user processes under same account
- **Administrator**: Required for cross-user and elevated processes
- **Debug Privilege**: Necessary for system processes and services

### Anti-Virus Behavior
- Lower detection probability compared to standard OpenProcess calls
- Handle enumeration may trigger security monitoring systems
- Unusual access patterns could generate behavioral alerts
- Code signing recommended for production deployments

### Best Practices
```cpp
// Minimize access rights to required operations only
HANDLE h = NtOP::OpenProcessForRead(pid);  // Only request necessary permissions

// Always validate handles before use
if (!NtOP::IsValidProcessHandle(h)) {
    // Handle validation failure appropriately
}

// Prompt cleanup to reduce detection window
NtOP::CloseProcessHandle(h);
```

## Troubleshooting

### Common Issues

**Returns INVALID_HANDLE_VALUE**
- Verify process ID exists using Task Manager or process enumeration
- Confirm sufficient privileges (try running as administrator)
- Check if target process has protection mechanisms active

**Handle validation fails**
- Process may have terminated between opening and validation
- Handle might have been closed prematurely
- Access rights insufficient for validation operations

**Access denied errors**
- Enable administrator privileges for the calling process
- Consider enabling SeDebugPrivilege for system process access
- Some processes cannot be accessed due to kernel protection


## Version History

### v1.0.0
- Initial implementation of NtOpenProcess wrapper functionality
- Handle management and validation utilities
- Convenience functions for common access patterns
- Anti-detection mechanisms and indirect API loading
