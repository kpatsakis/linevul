int32_t GetCallbackId() {
  static int32_t sCallId = 0;
  return ++sCallId;
}
