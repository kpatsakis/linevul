HRESULT CallDwmSetIconicLivePreviewBitmap(HWND window,
                                          HBITMAP bitmap,
                                          POINT* client,
                                          DWORD flags) {
  FilePath dwmapi_path(base::GetNativeLibraryName(L"dwmapi"));
  base::ScopedNativeLibrary dwmapi(dwmapi_path);

  typedef HRESULT (STDAPICALLTYPE *DwmSetIconicLivePreviewBitmapProc)(
      HWND, HBITMAP, POINT*, DWORD);
  DwmSetIconicLivePreviewBitmapProc dwm_set_live_preview_bitmap =
      static_cast<DwmSetIconicLivePreviewBitmapProc>(
      dwmapi.GetFunctionPointer("DwmSetIconicLivePreviewBitmap"));

  if (!dwm_set_live_preview_bitmap)
    return E_FAIL;

  return dwm_set_live_preview_bitmap(window, bitmap, client, flags);
}
