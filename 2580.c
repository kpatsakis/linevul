int BlacklistSize() {
  int size = -1;
  while (blacklist::g_troublesome_dlls[++size] != NULL) {}

  return size;
}
