bool BinaryUploadService::IsActive(Request* request) {
  return (active_requests_.find(request) != active_requests_.end());
}
