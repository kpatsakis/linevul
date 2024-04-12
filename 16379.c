void GLES2Implementation::OnGpuControlErrorMessage(const char* message,
                                                   int32_t id) {
  SendErrorMessage(message, id);
}
