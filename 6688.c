bool AllRootWindowsHaveLockedModalBackgrounds() {
  return AllRootWindowsHaveModalBackgroundsForContainer(
      kShellWindowId_LockSystemModalContainer);
}
