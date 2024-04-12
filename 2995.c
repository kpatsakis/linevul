INT_PTR CALLBACK UpdateCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int dy;
	RECT rect;
	REQRESIZE* rsz;
	HWND hPolicy;
	static HWND hFrequency, hBeta;
	int32_t freq;
	char update_policy_text[4096];
	static BOOL resized_already = TRUE;

	switch (message) {
	case WM_INITDIALOG:
		resized_already = FALSE;
		hUpdatesDlg = hDlg;
		apply_localization(IDD_UPDATE_POLICY, hDlg);
		SetTitleBarIcon(hDlg);
		CenterDialog(hDlg);
		hFrequency = GetDlgItem(hDlg, IDC_UPDATE_FREQUENCY);
		hBeta = GetDlgItem(hDlg, IDC_INCLUDE_BETAS);
		IGNORE_RETVAL(ComboBox_SetItemData(hFrequency, ComboBox_AddStringU(hFrequency, lmprintf(MSG_013)), -1));
		IGNORE_RETVAL(ComboBox_SetItemData(hFrequency, ComboBox_AddStringU(hFrequency, lmprintf(MSG_030, lmprintf(MSG_014))), 86400));
		IGNORE_RETVAL(ComboBox_SetItemData(hFrequency, ComboBox_AddStringU(hFrequency, lmprintf(MSG_015)), 604800));
		IGNORE_RETVAL(ComboBox_SetItemData(hFrequency, ComboBox_AddStringU(hFrequency, lmprintf(MSG_016)), 2629800));
		freq = ReadSetting32(SETTING_UPDATE_INTERVAL);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK_NOW), (freq != 0));
		EnableWindow(hBeta, (freq >= 0));
		switch(freq) {
		case -1:
			IGNORE_RETVAL(ComboBox_SetCurSel(hFrequency, 0));
			break;
		case 0:
		case 86400:
			IGNORE_RETVAL(ComboBox_SetCurSel(hFrequency, 1));
			break;
		case 604800:
			IGNORE_RETVAL(ComboBox_SetCurSel(hFrequency, 2));
			break;
		case 2629800:
			IGNORE_RETVAL(ComboBox_SetCurSel(hFrequency, 3));
			break;
		default:
			IGNORE_RETVAL(ComboBox_SetItemData(hFrequency, ComboBox_AddStringU(hFrequency, lmprintf(MSG_017)), freq));
			IGNORE_RETVAL(ComboBox_SetCurSel(hFrequency, 4));
			break;
		}
		IGNORE_RETVAL(ComboBox_AddStringU(hBeta, lmprintf(MSG_008)));
		IGNORE_RETVAL(ComboBox_AddStringU(hBeta, lmprintf(MSG_009)));
		IGNORE_RETVAL(ComboBox_SetCurSel(hBeta, ReadSettingBool(SETTING_INCLUDE_BETAS)?0:1));
		hPolicy = GetDlgItem(hDlg, IDC_POLICY);
		SendMessage(hPolicy, EM_AUTOURLDETECT, 1, 0);
		static_sprintf(update_policy_text, update_policy, lmprintf(MSG_179|MSG_RTF),
			lmprintf(MSG_180|MSG_RTF), lmprintf(MSG_181|MSG_RTF), lmprintf(MSG_182|MSG_RTF), lmprintf(MSG_183|MSG_RTF),
			lmprintf(MSG_184|MSG_RTF), lmprintf(MSG_185|MSG_RTF), lmprintf(MSG_186|MSG_RTF));
		SendMessageA(hPolicy, EM_SETTEXTEX, (WPARAM)&friggin_microsoft_unicode_amateurs, (LPARAM)update_policy_text);
		SendMessage(hPolicy, EM_SETSEL, -1, -1);
		SendMessage(hPolicy, EM_SETEVENTMASK, 0, ENM_LINK|ENM_REQUESTRESIZE);
		SendMessageA(hPolicy, EM_SETBKGNDCOLOR, 0, (LPARAM)GetSysColor(COLOR_BTNFACE));
		SendMessage(hPolicy, EM_REQUESTRESIZE, 0, 0);
		break;
	case WM_NOTIFY:
		if ((((LPNMHDR)lParam)->code == EN_REQUESTRESIZE) && (!resized_already)) {
			resized_already = TRUE;
			hPolicy = GetDlgItem(hDlg, IDC_POLICY);
			GetWindowRect(hPolicy, &rect);
			dy = rect.bottom - rect.top;
			rsz = (REQRESIZE *)lParam;
			dy -= rsz->rc.bottom - rsz->rc.top + 6;	// add the border
			ResizeMoveCtrl(hDlg, hDlg, 0, 0, 0, -dy, 1.0f);
			ResizeMoveCtrl(hDlg, hPolicy, 0, 0, 0, -dy, 1.0f);
			ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDS_UPDATE_SETTINGS_GRP), 0, -dy, 0, 0, 1.0f);
			ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDS_UPDATE_FREQUENCY_TXT), 0, -dy, 0, 0, 1.0f);
			ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDC_UPDATE_FREQUENCY), 0, -dy, 0, 0, 1.0f);
			ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDS_INCLUDE_BETAS_TXT), 0, -dy, 0, 0, 1.0f);
			ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDC_INCLUDE_BETAS), 0, -dy, 0, 0, 1.0f);
			ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDS_CHECK_NOW_GRP), 0, -dy, 0, 0, 1.0f);
			ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDC_CHECK_NOW), 0, -dy, 0, 0, 1.0f);
			ResizeMoveCtrl(hDlg, GetDlgItem(hDlg, IDCANCEL), 0, -dy, 0, 0, 1.0f);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCLOSE:
		case IDCANCEL:
			reset_localization(IDD_UPDATE_POLICY);
			EndDialog(hDlg, LOWORD(wParam));
			hUpdatesDlg = NULL;
			return (INT_PTR)TRUE;
		case IDC_CHECK_NOW:
			CheckForUpdates(TRUE);
			return (INT_PTR)TRUE;
		case IDC_UPDATE_FREQUENCY:
			if (HIWORD(wParam) != CBN_SELCHANGE)
				break;
			freq = (int32_t)ComboBox_GetItemData(hFrequency, ComboBox_GetCurSel(hFrequency));
			WriteSetting32(SETTING_UPDATE_INTERVAL, (DWORD)freq);
			EnableWindow(hBeta, (freq >= 0));
			return (INT_PTR)TRUE;
		case IDC_INCLUDE_BETAS:
			if (HIWORD(wParam) != CBN_SELCHANGE)
				break;
			WriteSettingBool(SETTING_INCLUDE_BETAS, ComboBox_GetCurSel(hBeta) == 0);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
