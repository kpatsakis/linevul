void EventReaderLibevdevCros::OnLogMessage(void* data,
                                           int level,
                                           const char* fmt,
                                           ...) {
  va_list args;
  va_start(args, fmt);
  if (level >= LOGLEVEL_ERROR)
    LOG(ERROR) << "libevdev: " << FormatLog(fmt, args);
  else if (level >= LOGLEVEL_WARNING)
    LOG(WARNING) << "libevdev: " << FormatLog(fmt, args);
  else
    VLOG(3) << "libevdev: " << FormatLog(fmt, args);
  va_end(args);
}
