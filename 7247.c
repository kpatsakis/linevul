bool HostNPScriptObject::Disconnect(const NPVariant* args,
                                    uint32_t arg_count,
                                    NPVariant* result) {
  CHECK_EQ(base::PlatformThread::CurrentId(), np_thread_id_);
  if (arg_count != 0) {
    SetException("disconnect: bad number of arguments");
    return false;
  }

  DisconnectInternal();

  return true;
}
