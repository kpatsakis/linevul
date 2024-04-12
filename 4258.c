void MediaStreamManager::HandleRequestDone(const std::string& label,
                                           DeviceRequest* request) {
  DCHECK(RequestDone(*request));
  DVLOG(1) << "HandleRequestDone("
           << ", {label = " << label << "})";

  switch (request->request_type()) {
    case MEDIA_OPEN_DEVICE_PEPPER_ONLY:
      FinalizeOpenDevice(label, request);
      OnStreamStarted(label);
      break;
    case MEDIA_GENERATE_STREAM: {
      FinalizeGenerateStream(label, request);
      break;
    }
    case MEDIA_DEVICE_UPDATE:
      OnStreamStarted(label);
      break;
    default:
      NOTREACHED();
      break;
  }
}
