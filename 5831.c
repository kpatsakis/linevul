void CheckClientDownloadRequest::SetDownloadPingToken(
    const std::string& token) {
  DCHECK(!token.empty());
  DownloadProtectionService::SetDownloadPingToken(item_, token);
}
