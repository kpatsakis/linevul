void WebRTCAudioDeviceTest::DestroyChannel() {
  DCHECK(content::BrowserThread::CurrentlyOn(content::BrowserThread::IO));
  audio_render_host_->OnChannelClosing();
  audio_render_host_->OnFilterRemoved();
  audio_input_renderer_host_->OnChannelClosing();
  audio_input_renderer_host_->OnFilterRemoved();
  channel_.reset();
  audio_render_host_ = NULL;
  audio_input_renderer_host_ = NULL;
}
