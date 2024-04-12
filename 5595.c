void MediaStreamManager::OnStreamStarted(const std::string& label) {
  DeviceRequest* const request = FindRequest(label);
  if (!request)
    return;

  if (request->ui_proxy) {
    request->ui_proxy->OnStarted(
        base::BindOnce(&MediaStreamManager::StopMediaStreamFromBrowser,
                       base::Unretained(this), label),
        base::BindOnce(&MediaStreamManager::OnMediaStreamUIWindowId,
                       base::Unretained(this), request->video_type(),
                       request->devices));
  }
}
