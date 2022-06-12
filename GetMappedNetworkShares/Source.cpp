

#define  STRICT
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string>

#pragma comment(lib, "mpr.lib")

// This function gets all the mapped network location
// (added by the command "net use Z: \\DEVICE-NAME-OR-IP\SHARED-FOLDER" for example.)
void getMappedNetworkLocations()
{
    TCHAR szDeviceName[256];
    DWORD dwResult, cchBuff = sizeof(szDeviceName);
    LPWSTR drive;
    char drive_chars[] = "a:";
    wchar_t wtext[3];

    while (strcmp(drive_chars, "{:")) // {: is the end of the drive list (this is the char after z in the ascii table)
    {
        mbstowcs(wtext, drive_chars, strlen(drive_chars) + 1);//Plus null
        drive = wtext;

        printf("Drive: %ls - ", drive);

        // Call the WNetGetConnection function.
        dwResult = WNetGetConnection((LPCWSTR)drive, szDeviceName, &cchBuff);

        // Print the connection name or process errors.
        switch (dwResult)
        {
        case NO_ERROR:
            printf("Connection name: %ls\n", szDeviceName);
            break;

            // The device is not a redirected device.
        case ERROR_NOT_CONNECTED:
            printf("The device is not a redirected device. (ERROR_NOT_CONNECTED)\n");
            break;

            // The device is not currently connected, but it is a persistent connection.
        case ERROR_CONNECTION_UNAVAIL:
            printf("The device is not currently connected, but it is a persistent connection. (ERROR_CONNECTION_UNAVAIL)\n");
            break;

            // Handle the error.
        default:
            printf("WNetGetConnection failed, Error: %d\n", dwResult);
        }
        drive_chars[0] += 1;
    }

}


int main(int argc, char* argv[])
{
    getMappedNetworkLocations();

    return 0;
}