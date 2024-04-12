void OnGpuProcessHostDestroyedOnUI(int host_id, const std::string& message) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  GpuDataManagerImpl::GetInstance()->AddLogMessage(
      logging::LOG_ERROR, "GpuProcessHostUIShim", message);
#if defined(USE_OZONE)
  ui::OzonePlatform::GetInstance()
      ->GetGpuPlatformSupportHost()
      ->OnChannelDestroyed(host_id);
#endif
}
