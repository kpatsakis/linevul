bool GenerateStateFromBeaconAndAttemptCount(HKEY* key, DWORD blacklist_state) {
  LONG result = 0;
  if (blacklist_state == blacklist::BLACKLIST_ENABLED) {
    return (SetDWValue(key,
                       blacklist::kBeaconAttemptCount,
                       static_cast<DWORD>(0)) == ERROR_SUCCESS);
  } else {
    DWORD attempt_count = 0;
    DWORD attempt_count_size = sizeof(attempt_count);
    result = ::RegQueryValueEx(*key,
                               blacklist::kBeaconAttemptCount,
                               0,
                               NULL,
                               reinterpret_cast<LPBYTE>(&attempt_count),
                               &attempt_count_size);

    if (result == ERROR_FILE_NOT_FOUND)
      attempt_count = 0;
    else if (result != ERROR_SUCCESS)
      return false;

    ++attempt_count;
    SetDWValue(key, blacklist::kBeaconAttemptCount, attempt_count);

    if (attempt_count >= blacklist::kBeaconMaxAttempts) {
      blacklist_state = blacklist::BLACKLIST_SETUP_FAILED;
      SetDWValue(key, blacklist::kBeaconState, blacklist_state);
    }

    return false;
  }
}
