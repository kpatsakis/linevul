void PepperMediaDeviceManager::CloseDevice(const std::string& label) {
#if defined(ENABLE_WEBRTC)
  GetMediaStreamDispatcher()->CloseDevice(label);
#endif
}
