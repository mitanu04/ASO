#include <windows.h>
#include <stdio.h>


int main() {
    HKEY hKey, hKeyRoot = HKEY_CURRENT_USER;
    LPCTSTR pszPath = TEXT("Control Panel\\Desktop");

    // Deschidere cheie
    DWORD result = RegOpenKeyEx(
        hKeyRoot,
        pszPath,
        0,
        KEY_ALL_ACCESS,
        &hKey
    );

    if (result != ERROR_SUCCESS) {
        wprintf(L"Eroare la cheie.\n");
        return 1;
    }

    wchar_t subKeyName[256];
    DWORD subKeyNameSize;
    DWORD index = 0;


    while (1) {
        subKeyNameSize = 256;

        result = RegEnumKeyEx(
            hKey,
            index,
            subKeyName,
            &subKeyNameSize,
            NULL,
            NULL,
            NULL,
            NULL
        );

        if (result == ERROR_NO_MORE_ITEMS) {
            break;
        }

        if (result == ERROR_SUCCESS) {
            wprintf(L"%s\n", subKeyName);
        }
        else {
            wprintf(L"Eroare la enumerare.\n");
            break;
        }

        index++;
    }

    RegCloseKey(hKey);
    return 0;
}