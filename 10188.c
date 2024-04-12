bool HostNPScriptObject::Invoke(const std::string& method_name,
                                const NPVariant* args,
                                uint32_t argCount,
                                NPVariant* result) {
  VLOG(2) << "Invoke " << method_name;
  CHECK_EQ(base::PlatformThread::CurrentId(), np_thread_id_);
  if (method_name == kFuncNameConnect) {
    return Connect(args, argCount, result);
  } else if (method_name == kFuncNameDisconnect) {
    return Disconnect(args, argCount, result);
  } else if (method_name == kFuncNameLocalize) {
    return Localize(args, argCount, result);
  } else {
    SetException("Invoke: unknown method " + method_name);
    return false;
  }
}
