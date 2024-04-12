int32_t WriteEntireBuffer(PP_Instance instance,
                          pp::FileIO* file_io,
                          int32_t offset,
                          const std::string& data,
                          CallbackType callback_type) {
  TestCompletionCallback callback(instance, callback_type);
  int32_t write_offset = offset;
  const char* buf = data.c_str();
  int32_t size = static_cast<int32_t>(data.size());

  while (write_offset < offset + size) {
    callback.WaitForResult(file_io->Write(write_offset,
                                          &buf[write_offset - offset],
                                          size - write_offset + offset,
                                          callback.GetCallback()));
    if (callback.result() < 0)
      return callback.result();
    if (callback.result() == 0)
      return PP_ERROR_FAILED;
    write_offset += callback.result();
  }

  return PP_OK;
}
