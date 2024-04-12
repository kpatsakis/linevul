void BinaryUploadService::Request::set_fcm_token(const std::string& token) {
  deep_scanning_request_.set_fcm_notification_token(token);
}
