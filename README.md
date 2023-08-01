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

