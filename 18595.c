INT_PTR CALLBACK ListCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT loc;
	int i, dh, r  = -1;
	static LRESULT disabled[9] = { HTLEFT, HTRIGHT, HTTOP, HTBOTTOM, HTSIZE,
		HTTOPLEFT, HTTOPRIGHT, HTBOTTOMLEFT, HTBOTTOMRIGHT };
	static HBRUSH background_brush, separator_brush;
	NONCLIENTMETRICS ncm;
	RECT rect, rect2;
	HFONT hDlgFont;
	HWND hCtrl;
	HDC hDC;

	switch (message) {
	case WM_INITDIALOG:
		if (nDialogItems > (IDC_LIST_ITEMMAX - IDC_LIST_ITEM1 + 1)) {
			uprintf("Warning: Too many items requested for List (%d vs %d)",
				nDialogItems, IDC_LIST_ITEMMAX - IDC_LIST_ITEM1);
			nDialogItems = IDC_LIST_ITEMMAX - IDC_LIST_ITEM1;
		}
		ncm.cbSize = sizeof(ncm);
#if defined(_MSC_VER) && (_MSC_VER >= 1500) && (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
		if (nWindowsVersion >= WINDOWS_VISTA) {
			ncm.cbSize -= sizeof(ncm.iPaddedBorderWidth);
		}
#endif
		SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
		hDlgFont = CreateFontIndirect(&(ncm.lfMessageFont));
		SendMessage(hDlg, WM_SETFONT, (WPARAM)hDlgFont, MAKELPARAM(TRUE, 0));
		SendMessage(GetDlgItem(hDlg, IDC_LIST_TEXT), WM_SETFONT, (WPARAM)hDlgFont, MAKELPARAM(TRUE, 0));
		for (i = 0; i < nDialogItems; i++)
			SendMessage(GetDlgItem(hDlg, IDC_LIST_ITEM1 + i), WM_SETFONT, (WPARAM)hDlgFont, MAKELPARAM(TRUE, 0));
		SendMessage(GetDlgItem(hDlg, IDYES), WM_SETFONT, (WPARAM)hDlgFont, MAKELPARAM(TRUE, 0));
		SendMessage(GetDlgItem(hDlg, IDNO), WM_SETFONT, (WPARAM)hDlgFont, MAKELPARAM(TRUE, 0));

		apply_localization(IDD_LIST, hDlg);
		background_brush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
		separator_brush = CreateSolidBrush(GetSysColor(COLOR_3DLIGHT));
		SetTitleBarIcon(hDlg);
		CenterDialog(hDlg);
		Static_SetIcon(GetDlgItem(hDlg, IDC_LIST_ICON), LoadIcon(NULL, IDI_EXCLAMATION));
		SetWindowTextU(hDlg, szMessageTitle);
		SetWindowTextU(GetDlgItem(hDlg, IDCANCEL), lmprintf(MSG_007));
		SetWindowTextU(GetDlgItem(hDlg, IDC_LIST_TEXT), szMessageText);
		for (i = 0; i < nDialogItems; i++) {
			SetWindowTextU(GetDlgItem(hDlg, IDC_LIST_ITEM1 + i), szDialogItem[i]);
			ShowWindow(GetDlgItem(hDlg, IDC_LIST_ITEM1 + i), SW_SHOW);
		}
		hCtrl = GetDlgItem(hDlg, IDC_LIST_TEXT);
		hDC = GetDC(hCtrl);
		SelectFont(hDC, hDlgFont);	// Yes, you *MUST* reapply the font to the DC, even after SetWindowText!
		GetWindowRect(hCtrl, &rect);
		dh = rect.bottom - rect.top;
		DrawTextU(hDC, szMessageText, -1, &rect, DT_CALCRECT | DT_WORDBREAK);
		dh = rect.bottom - rect.top - dh;
		if (hDC != NULL)
			ReleaseDC(hCtrl, hDC);
		ResizeMoveCtrl(hDlg, hCtrl, 0, 0, 0, dh, 1.0f);
		for (i = 0; i < nDialogItems; i++)
			ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDC_LIST_ITEM1 + i), 0, dh, 0, 0, 1.0f);
		if (nDialogItems > 1) {
			GetWindowRect(GetDlgItem(hDlg, IDC_LIST_ITEM1), &rect);
			GetWindowRect(GetDlgItem(hDlg, IDC_LIST_ITEM1 + nDialogItems - 1), &rect2);
			dh += rect2.top - rect.top;
		}
		ResizeMoveCtrl(hDlg, hDlg, 0, 0, 0, dh, 1.0f);
		ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, -1), 0, 0, 0, dh, 1.0f);	// IDC_STATIC = -1
		ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDC_LIST_LINE), 0, dh, 0, 0, 1.0f);
		ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDOK), 0, dh, 0, 0, 1.0f);
		ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDCANCEL), 0, dh, 0, 0, 1.0f);
		return (INT_PTR)TRUE;
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam, TRANSPARENT);
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_NOTIFICATION_LINE)) {
			return (INT_PTR)separator_brush;
		}
		return (INT_PTR)background_brush;
	case WM_NCHITTEST:
		loc = DefWindowProc(hDlg, message, wParam, lParam);
		for (i = 0; i < 9; i++) {
			if (loc == disabled[i]) {
				return (INT_PTR)TRUE;
			}
		}
		return (INT_PTR)FALSE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
		case IDNO:
		case IDCANCEL:
			EndDialog(hDlg, r);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
