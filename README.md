# ntapi-cpp

A lightweight C++ library providing direct access to Windows NT native APIs for system-level programming and process management.

## Why NT APIs?

Traditional Windows APIs like `CreateToolhelp32Snapshot` can be easily detected and blocked by security software. This library uses undocumented NT APIs that operate at the kernel level, providing:

- **Lower detection rates** by antivirus and security tools
- **Direct kernel communication** without Win32 layer overhead
- **Access to system information** not available through standard APIs
- **Better performance** for process enumeration and memory operations

## Available Modules

| Module | Description | Status | Documentation |
|--------|-------------|--------|---------------|
| **NtQuerySystemInformation** | Process enumeration and system info | ✅ Complete | [📖 Documentation](NtQuerySystemInformation/README.md) |
| **NtOpenProcess** | Advanced process handle management | 🚧 In Development | [📖 Documentation](NtOpenProcess/README.md) |
| **NtWriteVirtualMemory** | Direct memory manipulation | 📋 Planned | [📖 Documentation](NtWriteVirtualMemory/README.md) |
| **NtReadVirtualMemory** | Memory reading utilities | 📋 Planned | [📖 Documentation](NtReadVirtualMemory/README.md) |


## System Requirements

- **Operating System**: Windows 10/11 (x86/x64)
- **Compiler**: Visual Studio 2019+ or GCC 9+ with C++17 support
- **Dependencies**: Windows SDK only
- **Privileges**: Administrator recommended for full functionality

### Option 3: Integration Guide
1. Copy desired module folder to your project
2. Add `.cpp` files to your build system
3. Include the module headers
4. See module-specific README for detailed instructions

## Architecture Overview

```
ntapi-cpp/
├── README.md                    # This file - overview and getting started
├── NtQuerySystemInformation/    # Process enumeration module
│   ├── README.md               # Complete API documentation
│   ├── includes/               # Header files
│   └── src/                    # Implementation
├── NtOpenProcess/    # Process enumeration module
└── 
```

## Security Considerations

**Important Notice**: This library uses low-level Windows APIs that may trigger security software. Please be aware:

- **Antivirus Detection**: Some modules may be flagged due to their nature
- **Administrator Privileges**: Required for accessing system processes
- **Responsible Use**: Intended for legitimate system administration and development
- **Code Signing**: Recommended for production deployments

## Getting Help

Each module has comprehensive documentation:

- **[NtQuerySystemInformation](NtQuerySystemInformation/README.md)** - Process discovery and enumeration
- **API Reference** - Complete function signatures and parameters
- **Build Instructions** - Step-by-step integration guides
- **Troubleshooting** - Common issues and solutions
- **Security Notes** - Privilege requirements and best practices

## Development Roadmap

### Completed
- ✅ NtQuerySystemInformation with process enumeration
- ✅ Anti-detection mechanisms and random delays
- ✅ Dynamic memory management

### In Progress
- 🚧 NtOpenProcess for advanced handle management
- 🚧 Comprehensive error handling

### Planned
- 📋 Memory manipulation modules (Read/Write)
- 📋 Process creation and injection utilities
- 📋 Registry access through NT APIs
