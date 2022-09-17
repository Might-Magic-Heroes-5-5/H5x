#include "windows.h"
#include "Main.h"

/* This does not get executed for some reaosn */
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved ) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

auto loaded = false;
/* This function is imported and executed by H5.exe at start. It sets up all the hooks. */
extern "C" __declspec(dllexport) bool TrackingCount(void* a, char* b, int c, int d) {
    if (!loaded) {
        loaded = true;
        main();
    }
    return true;
}

