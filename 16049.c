void BrowseForFolder(void) {

	BROWSEINFOW bi;
	LPITEMIDLIST pidl;
	WCHAR *wpath;
	size_t i;
	HRESULT hr;
	IShellItem *psi = NULL;
	IShellItem *si_path = NULL;	// Automatically freed
	IFileOpenDialog *pfod = NULL;
	WCHAR *fname;
	char* tmp_path = NULL;

	dialog_showing++;
	if (nWindowsVersion >= WINDOWS_VISTA) {
		INIT_VISTA_SHELL32;
		if (IS_VISTA_SHELL32_AVAILABLE) {
			hr = CoCreateInstance(&CLSID_FileOpenDialog, NULL, CLSCTX_INPROC,
				&IID_IFileOpenDialog, (LPVOID)&pfod);
			if (FAILED(hr)) {
				uprintf("CoCreateInstance for FileOpenDialog failed: error %X\n", hr);
				pfod = NULL;	// Just in case
				goto fallback;
			}
			hr = pfod->lpVtbl->SetOptions(pfod, FOS_PICKFOLDERS);
			if (FAILED(hr)) {
				uprintf("Failed to set folder option for FileOpenDialog: error %X\n", hr);
				goto fallback;
			}
			wpath = utf8_to_wchar(szFolderPath);
			fname = NULL;
			if ((wpath != NULL) && (wcslen(wpath) >= 1)) {
				for (i = wcslen(wpath) - 1; i != 0; i--) {
					if (wpath[i] == L'\\') {
						wpath[i] = 0;
						fname = &wpath[i + 1];
						break;
					}
				}
			}

			hr = (*pfSHCreateItemFromParsingName)(wpath, NULL, &IID_IShellItem, (LPVOID)&si_path);
			if (SUCCEEDED(hr)) {
				if (wpath != NULL) {
					pfod->lpVtbl->SetFolder(pfod, si_path);
				}
				if (fname != NULL) {
					pfod->lpVtbl->SetFileName(pfod, fname);
				}
			}
			safe_free(wpath);

			hr = pfod->lpVtbl->Show(pfod, hMainDialog);
			if (SUCCEEDED(hr)) {
				hr = pfod->lpVtbl->GetResult(pfod, &psi);
				if (SUCCEEDED(hr)) {
					psi->lpVtbl->GetDisplayName(psi, SIGDN_FILESYSPATH, &wpath);
					tmp_path = wchar_to_utf8(wpath);
					CoTaskMemFree(wpath);
					if (tmp_path == NULL) {
						uprintf("Could not convert path\n");
					} else {
						static_strcpy(szFolderPath, tmp_path);
						safe_free(tmp_path);
					}
				} else {
					uprintf("Failed to set folder option for FileOpenDialog: error %X\n", hr);
				}
			} else if ((hr & 0xFFFF) != ERROR_CANCELLED) {
				uprintf("Could not show FileOpenDialog: error %X\n", hr);
				goto fallback;
			}
			pfod->lpVtbl->Release(pfod);
			dialog_showing--;
			return;
		}
fallback:
		if (pfod != NULL) {
			pfod->lpVtbl->Release(pfod);
		}
	}

	INIT_XP_SHELL32;
	memset(&bi, 0, sizeof(BROWSEINFOW));
	bi.hwndOwner = hMainDialog;
	bi.lpszTitle = utf8_to_wchar(lmprintf(MSG_106));
	bi.lpfn = BrowseInfoCallback;
	bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS |
		BIF_DONTGOBELOWDOMAIN | BIF_EDITBOX | 0x00000200;
	pidl = SHBrowseForFolderW(&bi);
	if (pidl != NULL) {
		CoTaskMemFree(pidl);
	}
	safe_free(bi.lpszTitle);
	dialog_showing--;
}
