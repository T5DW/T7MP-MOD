
#include <windows.h>
#include "console.h"

#pragma comment(linker, "/export:D3D11CoreCreateDevice=C:\\Windows\\System32\\d3d11.D3D11CoreCreateDevice")
#pragma comment(linker, "/export:D3D11CoreGetLayeredDeviceSize=C:\\Windows\\System32\\d3d11.D3D11CoreGetLayeredDeviceSize")
#pragma comment(linker, "/export:D3D11CoreRegisterLayers=C:\\Windows\\System32\\d3d11.D3D11CoreRegisterLayers")
#pragma comment(linker, "/export:D3D11CreateDevice=C:\\Windows\\System32\\d3d11.D3D11CreateDevice")
#pragma comment(linker, "/export:D3D11CreateDeviceAndSwapChain=C:\\Windows\\System32\\d3d11.D3D11CreateDeviceAndSwapChain")
#pragma comment(linker, "/export:D3D11On12CreateDevice=C:\\Windows\\System32\\d3d11.D3D11On12CreateDevice")
#pragma comment(linker, "/export:D3D11CreateDevice=C:\\Windows\\System32\\d3d11.D3D11CreateDevice")
#pragma comment(linker, "/export:D3D11CreateDeviceAndSwapChain=C:\\Windows\\System32\\d3d11.D3D11CreateDeviceAndSwapChain")

HMODULE g_d3d11 = nullptr;

void LoadOriginalD3D11()
{
    if (g_d3d11)
        return;

    char path[MAX_PATH];

    GetSystemDirectoryA(path, MAX_PATH);
    lstrcatA(path, "\\d3d11.dll");

    g_d3d11 = LoadLibraryA(path);
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD reason,
                      LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:

        DisableThreadLibraryCalls(hModule);

        LoadOriginalD3D11();

        CreateConsole();


        break;

    case DLL_PROCESS_DETACH:

        if (g_d3d11)
            FreeLibrary(g_d3d11);

        break;
    }

    return TRUE;
}

