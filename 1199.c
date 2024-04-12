void ContinueCheckingForFileExistence(
    content::CheckForFileExistenceCallback callback) {
  std::move(callback).Run(false);
}
