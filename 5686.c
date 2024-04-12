void VideoCaptureManager::OnDeviceLaunched(VideoCaptureController* controller) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  std::ostringstream string_stream;
  string_stream << "Launching device has succeeded. device_id = "
                << controller->device_id();
  EmitLogMessage(string_stream.str(), 1);
  DCHECK(!device_start_request_queue_.empty());
  DCHECK_EQ(controller, device_start_request_queue_.begin()->controller());
  DCHECK(controller);

  if (controller->stream_type() == MEDIA_GUM_DESKTOP_VIDEO_CAPTURE) {
    const media::VideoCaptureSessionId session_id =
        device_start_request_queue_.front().session_id();
    DCHECK(session_id != kFakeSessionId);
    MaybePostDesktopCaptureWindowId(session_id);
  }

  auto it = photo_request_queue_.begin();
  while (it != photo_request_queue_.end()) {
    auto request = it++;
    VideoCaptureController* maybe_entry =
        LookupControllerBySessionId(request->first);
    if (maybe_entry && maybe_entry->IsDeviceAlive()) {
      request->second.Run();
      photo_request_queue_.erase(request);
    }
  }

  device_start_request_queue_.pop_front();
  ProcessDeviceStartRequestQueue();
}
