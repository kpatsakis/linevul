void GLES2DecoderImpl::PerformIdleWork() {
  gpu_tracer_->ProcessTraces();
  ProcessPendingReadPixels(false);
}
