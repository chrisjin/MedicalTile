#include"DicomDllMain.h"
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            //QResource::registerResource("QrcCraft.rcc");
            break;

        case DLL_PROCESS_DETACH:
            
            break;

        case DLL_THREAD_ATTACH:
            //printf("Thread attach. \n");
            break;

        case DLL_THREAD_DETACH:
            //printf("Thread detach. \n");
            break;
    }

    return (TRUE);
}