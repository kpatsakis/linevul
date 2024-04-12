MediaStreamManager::FindRequest(const std::string& label) const {
  for (const LabeledDeviceRequest& labeled_request : requests_) {
    if (labeled_request.first == label)
      return labeled_request.second;
  }
  return nullptr;
}
