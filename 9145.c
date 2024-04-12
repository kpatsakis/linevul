  static void Initialize() {
    display::win::ScreenWin::SetRequestHDRStatusCallback(
        base::Bind(&HDRProxy::RequestHDRStatus));
  }
