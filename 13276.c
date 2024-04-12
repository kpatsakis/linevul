AudioServiceListener* MediaStreamManager::audio_service_listener() {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  return audio_service_listener_.get();
}
