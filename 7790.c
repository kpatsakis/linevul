error::Error GLES2DecoderImpl::HandleWaitAllAsyncTexImage2DCHROMIUM(
    uint32 immediate_data_size, const cmds::WaitAllAsyncTexImage2DCHROMIUM& c) {
  TRACE_EVENT0("gpu", "GLES2DecoderImpl::HandleWaitAsyncTexImage2DCHROMIUM");

  GetAsyncPixelTransferManager()->WaitAllAsyncTexImage2D();
  ProcessFinishedAsyncTransfers();
  return error::kNoError;
}
