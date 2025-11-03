#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define byte win_byte_override
#include <windows.h>
#include <psapi.h>
#undef byte

inline double getMemoryMB() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.WorkingSetSize / (1024.0 * 1024.0);
}
