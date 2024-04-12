void CrosMock::TearDownMocks() {
  if (loader_)
    test_api()->SetLibraryLoader(NULL, false);
  if (mock_cryptohome_library_)
    test_api()->SetCryptohomeLibrary(NULL, false);
  if (mock_network_library_)
    test_api()->SetNetworkLibrary(NULL, false);
  if (mock_power_library_)
    test_api()->SetPowerLibrary(NULL, false);
  if (mock_screen_lock_library_)
    test_api()->SetScreenLockLibrary(NULL, false);
  if (mock_speech_synthesis_library_)
    test_api()->SetSpeechSynthesisLibrary(NULL, false);
  if (mock_touchpad_library_)
    test_api()->SetTouchpadLibrary(NULL, false);
}
