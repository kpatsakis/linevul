struct tm* localtime_override(const time_t* timep) {
  if (g_am_zygote_or_renderer) {
    static struct tm time_struct;
    static char timezone_string[64];
    ProxyLocaltimeCallToBrowser(*timep, &time_struct, timezone_string,
                                sizeof(timezone_string));
    return &time_struct;
  }

  CHECK_EQ(0, pthread_once(&g_libc_localtime_funcs_guard,
                           InitLibcLocaltimeFunctions));
  struct tm* res = g_libc_localtime(timep);
#if defined(MEMORY_SANITIZER)
  if (res) __msan_unpoison(res, sizeof(*res));
  if (res->tm_zone) __msan_unpoison_string(res->tm_zone);
#endif
  return res;
}
