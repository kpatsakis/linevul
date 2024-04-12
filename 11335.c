static void safe_close_(int *fd) {
  assert(fd != NULL);
 if (*fd != -1) {
    close(*fd);
 *fd = -1;
 }
}
