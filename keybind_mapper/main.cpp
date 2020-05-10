//John Hua
//3.25.2020
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>
#include <PathCch.h>
#include <Shlwapi.h>
#pragma comment(lib, "Pathcch.lib")

using namespace std;

bool keyPress(int vcode) {
    return GetAsyncKeyState(vcode) & ~32767;
}


/*Keybind mapper with some test functions using keybinds to toggle a boolean,
  manually setting values, and incrementing/decrementing. May be useful to
  create keybind shortcuts to serve a different functionality besides the
  aforementioned. Configurable using a config.ini file.
  
  Use keybind mapper to get the virtual keycode and then assign the number
  to the desired functionality in the config.ini file.*/

int main() {

    bool toggleMode = false;
    int setMode = 1;
    int vkey[200] = {};

    for (int i = 0; i < 200; i++)
    {
        vkey[i] = i + 1;
    }


    WCHAR config[MAX_PATH] = {};
    GetModuleFileNameW(NULL, config, MAX_PATH);
    PathCchRemoveFileSpec(config, MAX_PATH);
    PathCchCombine(config, MAX_PATH, config, L"config.ini");

    cout << "F9 - Keybind Mapper" << endl;
    cout << "F10 - Terminate" << endl;

    while (!keyPress(121)) {

        /*Configuration*/
        int pull_Str = GetPrivateProfileInt(L"Option", L"pull_Str", 2, config);
        int mode1_delay = GetPrivateProfileInt(L"Option", L"mode1_delay", 7, config);
        int mode2_delay = GetPrivateProfileInt(L"Option", L"mode2_delay", 6, config);
        int mode3_delay = GetPrivateProfileInt(L"Option", L"mode3_delay", 5, config);
        int mode4_delay = GetPrivateProfileInt(L"Option", L"mode4_delay", 4, config);

        /*Keybinds*/
        int incrementMode = GetPrivateProfileInt(L"Keybinds", L"incrementMode", 6, config);
        int decrementMode = GetPrivateProfileInt(L"Keybinds", L"decrementMode", 5, config);
        int toggleKeybind = GetPrivateProfileInt(L"Keybinds", L"toggleRecoil", 4, config);
        int manual_Mode1 = GetPrivateProfileInt(L"Keybinds", L"manual_Mode1", 0, config);
        int manual_Mode2 = GetPrivateProfileInt(L"Keybinds", L"manual_Mode2", 0, config);
        int manual_Mode3 = GetPrivateProfileInt(L"Keybinds", L"manual_Mode3", 0, config);
        int manual_Mode4 = GetPrivateProfileInt(L"Keybinds", L"manual_Mode4", 0, config);
        int LMB = GetPrivateProfileInt(L"Keybinds", L"LMB", 1, config);
        int RMB = GetPrivateProfileInt(L"Keybinds", L"RMB", 2, config);

        /*Keybind Mapper*/
        if (keyPress(120)) {
            while (keyPress(120)) {
                Sleep(20);
            }
            cout << "Keybind mapper enabled. Press 'ESC' to exit" << endl << endl;
            do {
                for (int i = 0; i < 200; i++) {
                    if (keyPress(vkey[i])) {
                        while (keyPress(vkey[i])) {
                            Sleep(20);
                        }
                        cout << "Key value: " << vkey[i] << endl;
                        break;
                    }
                }
            } while (!keyPress(27));
            cout << "Exited keybind mapper" << endl << endl;
        }


        /*Test function to toggle a mode on or off*/
        if (keyPress(toggleKeybind)) {
            while (keyPress(toggleKeybind)) {
                Sleep(20);
            }
            toggleMode = !toggleMode;
            toggleMode ? cout << "Mode: ON" << endl : cout << "Mode: OFF" << endl;
        }

        /*Manually set mode to a value depending on the keybind for manual_Mode*/
        if (keyPress(manual_Mode1)) {
            while (keyPress(manual_Mode1)) {
                Sleep(20);
            }
            setMode = 1;
            cout << "Mode set to: " << setMode << endl;
        }

        if (keyPress(manual_Mode2)) {
            while (keyPress(manual_Mode2)) {
                Sleep(20);
            }
            setMode = 2;
            cout << "Mode set to: " << setMode << endl;
        }

        if (keyPress(manual_Mode3)) {
            while (keyPress(manual_Mode3)) {
                Sleep(20);
            }
            setMode = 3;
            cout << "Mode set to: " << setMode << endl;
        }

        if (keyPress(manual_Mode4)) {
            while (keyPress(manual_Mode4)) {
                Sleep(20);
            }
            setMode = 4;
            cout << "Mode set to: " << setMode << endl;
        }


        /*Linear Decrement/Incrementing Manual Modes with keybind*/
        if (keyPress(decrementMode)) {
            while (keyPress(decrementMode)) {
                Sleep(20);
            }
            if (setMode > 1) {
                setMode--;
                cout << "Mode decreased to: " << setMode << endl;
            }
            else cout << "Mode out of bounds" << endl;
        }

        if (keyPress(incrementMode)) {
            while (keyPress(incrementMode)) {
                Sleep(20);
            }
            if (setMode < 4) {
                setMode++;
                cout << "Mode increased to: " << setMode << endl;
            }
            else cout << "Mode out of bounds." << endl;
        }

        Sleep(25);
    }




    return 0;
}