# NtQuerySystemInformation Module

Advanced process enumeration using the native `NtQuerySystemInformation` API.

## 🎯 Features

- **Process Discovery**: Find processes by executable name
- **System Information**: Access detailed process data
- **Anti-Detection**: Built-in random delays to avoid automation detection
- **Memory Efficient**: Dynamic buffer allocation

## 📋 Requirements

- Windows 10/11 (any edition)
- Visual Studio 2019+ or compatible C++17 compiler
- Windows SDK

## 🚀 Quick Start

### Basic Usage

```cpp
#include "includes/NtQSI.h"
#include <iostream>

int main() {
    // Find a process by name
    DWORD pid = NtQSI::FindProcessIdByName(L"explorer.exe");
    
    if (pid != 0) {
        std::wcout << L"Explorer PID: " << pid << std::endl;
    } else {
        std::wcout << L"Explorer not found" << std::endl;
    }
    
    return 0;
}
```

### Integration into Existing Project

```cpp
// Add to your includes
#include "path/to/NtQuerySystemInformation/includes/NtQSI.h"

// Add to your build
// Visual Studio: Add NtQuerySystemInformation/src/NtQSI.cpp to Source Files
```

## 📖 API Reference

### `FindProcessIdByName(const std::wstring& processName)`

Searches for a running process by its executable name.

#### Parameters
- `processName` (const std::wstring&): The name of the executable to search for
  - Include the file extension (e.g., `L"notepad.exe"`)
  - Case-sensitive matching

#### Return Value
- `DWORD`: The Process ID (PID) if found, or `0` if not found

## 🛠️ Build Instructions

### Visual Studio

1. **Add Source File**:
   ```
   Solution Explorer → Source Files → Add → Existing Item
   Select: src/NtQSI.cpp
   ```

2. **Add Headers**:
   ```
   Solution Explorer → Header Files → Add → Existing Item
   Select: includes/NtQSI.h and includes/NtQSI_Structs.h
   ```

3. **Include in Code**:
   ```cpp
   #include "NtQuerySystemInformation/includes/NtQSI.h"
   ```

## 🔧 Advanced Usage

### Error Handling

```cpp
DWORD pid = NtQSI::FindProcessIdByName(L"nonexistent.exe");
if (pid == 0) {
    std::wcerr << L"Process not found or access denied" << std::endl;
    // Handle error appropriately
}
```

### Working with Multiple Processes

```cpp
// Note: Function returns the first match found
// For processes with multiple instances (like chrome.exe),
// only the first PID will be returned
DWORD chrome_pid = NtQSI::FindProcessIdByName(L"chrome.exe");
```

## ⚡ Performance

- **Average lookup time**: ~1-3ms for typical system (50-200 processes)
- **Memory usage**: ~256KB initial buffer, scales automatically
- **Anti-detection delay**: 1-6 seconds random delay per call

## 🛡️ Security Considerations

### Privileges Required
- **Standard User**: Can enumerate most user processes
- **Administrator**: Required for system processes and services
- **Debug Privilege**: Recommended for complete process access

### Anti-Virus Behavior
- May trigger heuristic detection due to `NtQuerySystemInformation` usage
- The random delay feature may be flagged as evasion technique
- Consider code signing for production use

### Best Practices
```cpp
// Check if running as administrator when needed
if (!IsUserAnAdmin()) {
    std::wcout << L"Some processes may not be visible without admin rights" << std::endl;
}

// Handle access denied gracefully
DWORD pid = NtQSI::FindProcessIdByName(L"csrss.exe");  // System process
if (pid == 0) {
    // May fail without proper privileges
}
```

## 🐛 Troubleshooting

### Common Issues

**Process Not Found (Returns 0)**
- Verify exact executable name including extension
- Check if process is actually running (Task Manager)
- Ensure sufficient privileges for system processes

**Compilation Errors**
```cpp
// Ensure all required headers are included
#include <windows.h>  // Must be first
#include <string>
#include <memory>
```

**Linker Errors**
- Verify `NtQSI.cpp` is added to your project's source files
- Check that include paths are correct


## 🔄 Version History

### v1.0.0
- ✅ Initial implementation
- ✅ Process enumeration by name
- ✅ Anti-detection random delays
- ✅ Dynamic buffer management
