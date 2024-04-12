void SupervisedUserService::AddExtensionUpdateRequest(
    const std::string& extension_id,
    const base::Version& version,
    SuccessCallback callback) {
  std::string id = GetExtensionRequestId(extension_id, version);
  AddPermissionRequestInternal(
      base::BindRepeating(CreateExtensionUpdateRequest, id),
      std::move(callback), 0);
}
