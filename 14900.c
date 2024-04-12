void PepperMediaDeviceManager::StopEnumerateDevices(int request_id) {
  enumerate_callbacks_.erase(request_id);

#if defined(ENABLE_WEBRTC)
  base::MessageLoop::current()->PostTask(
      FROM_HERE,
      base::Bind(&PepperMediaDeviceManager::StopEnumerateDevicesDelayed,
                 AsWeakPtr(),
                 request_id));
#endif
}
