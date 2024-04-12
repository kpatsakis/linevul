void MediaStreamManager::DeleteRequest(const std::string& label) {
  DVLOG(1) << "DeleteRequest({label= " << label << "})";
  for (DeviceRequests::iterator request_it = requests_.begin();
       request_it != requests_.end(); ++request_it) {
    if (request_it->first == label) {
      std::unique_ptr<DeviceRequest> request(request_it->second);
      requests_.erase(request_it);
      return;
    }
  }
  NOTREACHED();
}
