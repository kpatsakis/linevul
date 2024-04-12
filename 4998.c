static void CALLBACK FormatPromptHook(HWINEVENTHOOK hWinEventHook, DWORD Event, HWND hWnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
	char str[128];
	BOOL found;

	if (Event == EVENT_SYSTEM_FOREGROUND) {
		if (GetWindowLong(hWnd, GWL_STYLE) & WS_POPUPWINDOW) {
			str[0] = 0;
			GetWindowTextU(hWnd, str, sizeof(str));
			if (safe_strcmp(str, fp_title_str) == 0) {
				found = FALSE;
				EnumChildWindows(hWnd, FormatPromptCallback, (LPARAM)&found);
				if (found) {
					SendMessage(hWnd, WM_COMMAND, (WPARAM)IDCANCEL, (LPARAM)0);
					uprintf("Closed Windows format prompt");
				}
			}
		}
	}
}
