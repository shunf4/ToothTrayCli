# ToothTray-CLI

A Win32 CLI to list, show status of, and connect/disconnect with (already paired) bluetooth audio devices.

This is a fork; the original project is a beautiful GUI tray icon app: https://github.com/m2jean/ToothTray

```
D:\work\ToothTray\x64\Release>.\ToothTray.exe  -h
toothtray-cli list
toothtray-cli is-connected "My Device"
toothtray-cli is-connected-by-container-id {xxx}
toothtray-cli connect[-by-container-id] [-f] ...
toothtray-cli disconnect[-by-container-id] [-f] ...
```

```
D:\work\ToothTray\x64\Release>.\ToothTray.exe
0 {EF32B9DE-F90F-5577-AA6C-F391D3C8D18A} WH-H910N (h.ear)
0 {95DADBC3-F526-5D8C-9943-11767210C79F} MDR-XB80BS
1 {3A6D7ACB-8449-563D-BC4E-2E46D9594AA3} SOUNDPEATS RunFree

D:\work\ToothTray\x64\Release>.\ToothTray.exe is-connected "SOUNDPEATS RunFree"
1

D:\work\ToothTray\x64\Release>.\ToothTray.exe disconnect "SOUNDPEATS RunFree"

D:\work\ToothTray\x64\Release>.\ToothTray.exe connect-by-container-id {3A6D7ACB-8449-563D-BC4E-2E46D9594AA3}

D:\work\ToothTray\x64\Release>
```

