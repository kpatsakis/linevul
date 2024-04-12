bool CheckClientDownloadRequest::ShouldUploadBinary(
    DownloadCheckResultReason reason) {
  bool upload_for_dlp = ShouldUploadForDlpScan();
  bool upload_for_malware = ShouldUploadForMalwareScan(reason);
  if (!upload_for_dlp && !upload_for_malware)
    return false;

  return !!Profile::FromBrowserContext(GetBrowserContext());
}
