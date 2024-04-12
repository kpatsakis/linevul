float MinGlowAlphaToDisableRefresh() {
  if (IsAndroidLOrNewer())
    return kMinGlowAlphaToDisableRefreshOnL;

  return 1.01f;
}
