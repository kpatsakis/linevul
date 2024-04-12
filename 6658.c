void RenderViewImpl::SuspendVideoCaptureDevices(bool suspend) {
#if BUILDFLAG(ENABLE_WEBRTC)
  if (!main_render_frame_)
    return;

  MediaStreamDeviceObserver* media_stream_device_observer =
      main_render_frame_->GetMediaStreamDeviceObserver();
  if (!media_stream_device_observer)
    return;

  MediaStreamDevices video_devices =
      media_stream_device_observer->GetNonScreenCaptureDevices();
  RenderThreadImpl::current()->video_capture_impl_manager()->SuspendDevices(
      video_devices, suspend);
#endif  // BUILDFLAG(ENABLE_WEBRTC)
}
