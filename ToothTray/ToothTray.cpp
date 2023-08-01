// ToothTray.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ToothTray.h"
#include <memory>
#include <cstdio>
#include <functional>
#include <winrt/base.h>

#include "debuglog.h"
#include "BluetoothAudioDevices.h"
#include "TrayIcon.h"
#include "ToothTrayMenu.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
constexpr UINT WM_TRAYICON = WM_APP;

BluetoothAudioDeviceEnumerator bluetoothAudioDeviceEmumerator;
ToothTrayMenu trayMenu;
TrayIcon trayIcon;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int wmain(int argc, wchar_t* argv[]) {
    winrt::init_apartment();
    std::vector<BluetoothConnector> connectors = bluetoothAudioDeviceEmumerator.EnumerateAudioDevices();

    std::setlocale(LC_ALL, "");

    const wchar_t* command = L"list";
    if (argc >= 2) {
        command = argv[1];
    }
  
    if (lstrcmpW(command, L"list") == 0) {
        for (std::vector<BluetoothConnector>::iterator ite = connectors.begin(); ite != connectors.end(); ++ite) {
            std::wstring deviceName = std::wstring(ite->DeviceName());
            bool checked = ite->IsConnected();

            wprintf(L"%ls %ls %ls\n", checked ? L"1" : L"0", std::wstring(ite->ContainerId()).c_str(), deviceName.c_str());
        }
        return 0;
    } else if(lstrcmpW(command, L"is-connected") == 0 && argc >= 3) {
        const wchar_t* isConnectedArg = argv[2];
        bool found = false;

        for (std::vector<BluetoothConnector>::iterator ite = connectors.begin(); ite != connectors.end(); ++ite) {
            std::wstring deviceName = std::wstring(ite->DeviceName());
            bool checked = ite->IsConnected();

            if (lstrcmpW(isConnectedArg, deviceName.c_str()) == 0) {
                wprintf(checked ? L"1\n" : L"0\n");
                found = true;
                break;
            }
        }
        if (!found) {
            fwprintf(stderr, L"device not found (2)\n");
            return 2;
        }
        return 0;
    }
    else if (lstrcmpW(command, L"is-connected-by-container-id") == 0 && argc >= 3) {
        const wchar_t* isConnectedArg = argv[2];
        bool found = false;

        for (std::vector<BluetoothConnector>::iterator ite = connectors.begin(); ite != connectors.end(); ++ite) {
            bool checked = ite->IsConnected();

            if (lstrcmpW(isConnectedArg, std::wstring(ite->ContainerId()).c_str()) == 0) {
                wprintf(checked ? L"1\n" : L"0\n");
                found = true;
                break;
            }
        }
        if (!found) {
            fwprintf(stderr, L"device not found (2)\n");
            return 2;
        }
        return 0;
    }
    else if (lstrcmpW(command, L"connect") == 0 && argc >= 3) {
        const wchar_t* connectArg = argv[2];

        bool force = false;
        if (argc >= 4 && lstrcmpW(argv[2], L"-f") == 0) {
            connectArg = argv[3];
            force = true;
        }

        bool found = false;

        for (std::vector<BluetoothConnector>::iterator ite = connectors.begin(); ite != connectors.end(); ++ite) {
            if (lstrcmpW(connectArg, std::wstring(ite->DeviceName()).c_str()) == 0) {
                ite->Connect();
                found = true;
                break;
            }
        }
        if (!found) {
            fwprintf(stderr, L"device not found (2)\n");
            return 2;
        }
        return 0;
    }
    else if (lstrcmpW(command, L"connect-by-container-id") == 0 && argc >= 3) {
        const wchar_t* connectArg = argv[2];

        bool force = false;
        if (argc >= 4 && lstrcmpW(argv[2], L"-f") == 0) {
            connectArg = argv[3];
            force = true;
        }

        bool found = false;

        for (std::vector<BluetoothConnector>::iterator ite = connectors.begin(); ite != connectors.end(); ++ite) {
            if (lstrcmpW(connectArg, std::wstring(ite->ContainerId()).c_str()) == 0) {
                if (force || !ite->IsConnected()) {
                    ite->Connect();
                }
                found = true;
                break;
            }
        }
        if (!found) {
            fwprintf(stderr, L"device not found (2)\n");
            return 2;
        }
        return 0;
    }
    else if (lstrcmpW(command, L"connect-by-container-id") == 0 && argc >= 3) {
        const wchar_t* connectArg = argv[2];

        bool force = false;
        if (argc >= 4 && lstrcmpW(argv[2], L"-f") == 0) {
            connectArg = argv[3];
            force = true;
        }

        bool found = false;

        for (std::vector<BluetoothConnector>::iterator ite = connectors.begin(); ite != connectors.end(); ++ite) {
            if (lstrcmpW(connectArg, std::wstring(ite->ContainerId()).c_str()) == 0) {
                if (force || !ite->IsConnected()) {
                    ite->Connect();
                }
                found = true;
                break;
            }
        }
        if (!found) {
            fwprintf(stderr, L"device not found (2)\n");
            return 2;
        }
        return 0;
    }
    else if (lstrcmpW(command, L"disconnect") == 0 && argc >= 3) {
        const wchar_t* connectArg = argv[2];

        bool force = false;
        if (argc >= 4 && lstrcmpW(argv[2], L"-f") == 0) {
            connectArg = argv[3];
            force = true;
        }

        bool found = false;

        for (std::vector<BluetoothConnector>::iterator ite = connectors.begin(); ite != connectors.end(); ++ite) {
            if (lstrcmpW(connectArg, std::wstring(ite->DeviceName()).c_str()) == 0) {
                if (force || ite->IsConnected()) {
                    ite->Disconnect();
                }
                found = true;
                break;
            }
        }
        if (!found) {
            fwprintf(stderr, L"device not found (2)\n");
            return 2;
        }
        return 0;
    }
    else if (lstrcmpW(command, L"disconnect-by-container-id") == 0 && argc >= 3) {
        const wchar_t* connectArg = argv[2];

        bool force = false;
        if (argc >= 4 && lstrcmpW(argv[2], L"-f") == 0) {
            connectArg = argv[3];
            force = true;
        }

        bool found = false;

        for (std::vector<BluetoothConnector>::iterator ite = connectors.begin(); ite != connectors.end(); ++ite) {
            if (lstrcmpW(connectArg, std::wstring(ite->ContainerId()).c_str()) == 0) {
                if (force || ite->IsConnected()) {
                    ite->Disconnect();
                }
                found = true;
                break;
            }
        }
        if (!found) {
            fwprintf(stderr, L"device not found (2)\n");
            return 2;
        }
        return 0;
    }
    
    const wchar_t* helpText = L"toothtray-cli list\ntoothtray-cli is-connected \"My Device\"\ntoothtray-cli is-connected-by-container-id {xxx}\ntoothtray-cli connect[-by-container-id] [-f] ...\ntoothtray-cli disconnect[-by-container-id] [-f] ...\n";

    if (lstrcmpW(command, L"-h") == 0 || lstrcmpW(command, L"--help") == 0) {
        fwprintf(stdout, helpText);
    }
    else {
        fwprintf(stderr, helpText);
    }

    return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    winrt::init_apartment();

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TOOTHTRAY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TOOTHTRAY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TOOTHTRAY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //bluetoothRadio = BluetoothRadio::FindFirst();
   //bluetoothRadio.RegisterDeviceChange(hWnd);
   //watcher = std::make_unique<BluetoothDeviceWatcher>();
   //watcher->Start();

   HICON hIcon = (HICON)LoadImageW(hInstance, MAKEINTRESOURCE(IDI_TOOTHTRAY), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
   trayIcon.Initialize(hWnd, hIcon, 0, WM_TRAYICON, NULL);

   //ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int commandId = LOWORD(wParam);
            // Parse the menu selections:
            switch (commandId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                if (trayMenu.TryHandleCommand(commandId))
                    break;

                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    //case WM_DEVICECHANGE:
    //    BluetoothRadio::HandleDeviceChangeMessage(wParam, lParam);
    //    break;
    default:
        WORD event;
        if (trayIcon.HandleMessage(message, lParam, &event)) {
            if (event == WM_CONTEXTMENU || event == NIN_SELECT || event == NIN_KEYSELECT) {
                std::vector<BluetoothConnector> connectors = bluetoothAudioDeviceEmumerator.EnumerateAudioDevices();
                trayMenu.BuildMenu(connectors);
                trayMenu.ShowPopupMenu(hWnd, wParam);
            }
            break;
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
