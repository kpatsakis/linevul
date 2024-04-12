void BinaryUploadService::OnGetResponse(Request* request,
                                        DeepScanningClientResponse response) {
  if (!IsActive(request))
    return;

  if (response.has_dlp_scan_verdict()) {
    received_dlp_verdicts_[request].reset(response.release_dlp_scan_verdict());
  }

  if (response.has_malware_scan_verdict()) {
    received_malware_verdicts_[request].reset(
        response.release_malware_scan_verdict());
  }

  MaybeFinishRequest(request);
}
