static future_t *clean_up(void) {
  gki_buffer_cleanup();

  pthread_mutex_destroy(&gki_cb.lock);
 return NULL;
}
