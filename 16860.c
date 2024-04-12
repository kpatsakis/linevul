ChromeMetricsServiceClient::CreateUploader(
    base::StringPiece server_url,
    base::StringPiece insecure_server_url,
    base::StringPiece mime_type,
    metrics::MetricsLogUploader::MetricServiceType service_type,
    const metrics::MetricsLogUploader::UploadCallback& on_upload_complete) {
  return std::make_unique<metrics::NetMetricsLogUploader>(
      g_browser_process->shared_url_loader_factory(), server_url,
      insecure_server_url, mime_type, service_type, on_upload_complete);
}
