base::Optional<CameraCalibration> VideoCaptureManager::GetCameraCalibration(
    const std::string& device_id) {
  media::VideoCaptureDeviceInfo* info = GetDeviceInfoById(device_id);
  if (!info)
    return base::Optional<CameraCalibration>();
  return info->descriptor.camera_calibration;
}
