 static int sortfunc(const void *a, const void *b) {
  off_t diff = 
    ((* ((struct mschmd_file **) a))->offset) -
    ((* ((struct mschmd_file **) b))->offset);
  return (diff < 0) ? -1 : ((diff > 0) ? 1 : 0);
}
