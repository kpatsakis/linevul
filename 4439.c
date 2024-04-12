OverrideVideoCaptureDeviceFactory(
    std::unique_ptr<media::VideoCaptureDeviceFactory> platform_factory) {
  return base::WrapUnique(
      new VideoCaptureDeviceFactoryLinux(std::move(platform_factory)));
}
