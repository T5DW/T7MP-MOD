
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <filesystem>

#include "console.h"

namespace fs = std::filesystem;

void ReloadLobby()
{

    std::cout << "[GAME] Lobby refreshed" << std::endl;

}

std::string FindAccountNamePath()
{
    char exePath[MAX_PATH];
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);

    fs::path gameDir = fs::path(exePath).parent_path();

    fs::path accountPath =
        gameDir /
        "steam_settings" /
        "settings" /
        "account_name.txt";

    return accountPath.string();
}

void HandlePlayerName(const std::string& newName)
{
    std::string path = FindAccountNamePath();

    if (!fs::exists(path))
    {
        std::cout << "account_name.txt not found" << std::endl;
       std::cout << "Making steam_settings folder!" << std::endl;
        return;
    }

    std::ofstream file(path, std::ios::trunc);

    if (!file.is_open())
    {
        std::cout << "failed to open account_name.txt" << std::endl;
        return;
    }

    file << newName;
    file.close();

    std::cout << "Name changed to: " << newName << std::endl;
    std::cout << "To Make the Name work please Restart your T7MP-MOD " << std::endl;
}

void ConsoleThread()
{
    std::string input;

    while (true)
    {
        std::getline(std::cin, input);

        if (input.rfind("playername ", 0) == 0)
        {
            std::string newName = input.substr(11);

            if (!newName.empty())
            {
                HandlePlayerName(newName);
            }
        }
        else if (input == "refresh")
        {
            ReloadLobby();
        }
        else if (input == "help")
        {
            std::cout << std::endl;
            std::cout << "Commands:" << std::endl;
            std::cout << "playername <name>" << std::endl;
            std::cout << "refresh" << std::endl;
            std::cout << "help" << std::endl;
            std::cout << std::endl;
        }
    }
}

void CreateConsole()
{
    AllocConsole();

    FILE* fp;

    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);

    SetConsoleTitleA("T7-MP-MOD");
    std::cout << "D3D11 Injected!" << std::endl;
    std::cout << "Type 'help' for commands." << std::endl;

    std::thread(ConsoleThread).detach();
}
