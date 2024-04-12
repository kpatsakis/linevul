void MediaStreamManager::FinalizeGenerateStream(const std::string& label,
                                                DeviceRequest* request) {
  DVLOG(1) << "FinalizeGenerateStream label " << label;
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  DCHECK(request->generate_stream_cb);

  MediaStreamDevices audio_devices, video_devices;
  for (const MediaStreamDevice& device : request->devices) {
    if (IsAudioInputMediaType(device.type))
      audio_devices.push_back(device);
    else if (IsVideoMediaType(device.type))
      video_devices.push_back(device);
    else
      NOTREACHED();
  }

  std::move(request->generate_stream_cb)
      .Run(MEDIA_DEVICE_OK, label, audio_devices, video_devices);
}
