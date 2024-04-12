void MediaStreamManager::WillDestroyCurrentMessageLoop() {
  DVLOG(3) << "MediaStreamManager::WillDestroyCurrentMessageLoop()";
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO) ||
         !BrowserThread::IsThreadInitialized(BrowserThread::IO));
  if (media_devices_manager_)
    media_devices_manager_->StopMonitoring();
  if (video_capture_manager_)
    video_capture_manager_->UnregisterListener(this);
  if (audio_input_device_manager_)
    audio_input_device_manager_->UnregisterListener(this);

  audio_input_device_manager_ = nullptr;
  video_capture_manager_ = nullptr;
  media_devices_manager_ = nullptr;
  g_media_stream_manager_tls_ptr.Pointer()->Set(nullptr);
  requests_.clear();
}
