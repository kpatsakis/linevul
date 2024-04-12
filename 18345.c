  void SendAlternateCut() {
    if (TestingNativeMac())
      SendKeyEvent(ui::VKEY_X, false, true);
    else
      SendKeyEvent(ui::VKEY_DELETE, true, false);
  }
