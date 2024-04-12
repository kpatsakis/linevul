void BinaryUploadService::ResetAuthorizationData() {
  can_upload_data_ = base::nullopt;

  IsAuthorized(base::DoNothing());
}
