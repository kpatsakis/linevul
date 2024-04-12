void WebGraphicsContext3DCommandBufferImpl::finish() {
  gl_->Finish();
  if (!visible_ && free_command_buffer_when_invisible_)
    gl_->FreeEverything();
}
