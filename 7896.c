void GLES2Implementation::FinishHelper() {
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glFinish()");
  TRACE_EVENT0("gpu", "GLES2::Finish");
  helper_->Finish();
  helper_->CommandBufferHelper::Finish();

  if (aggressively_free_resources_)
    FreeEverything();
}
