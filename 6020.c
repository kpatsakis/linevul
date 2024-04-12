DownloadManagerImpl::UniqueUrlDownloadHandlerPtr BeginDownload(
    std::unique_ptr<DownloadUrlParameters> params,
    content::ResourceContext* resource_context,
    uint32_t download_id,
    base::WeakPtr<DownloadManagerImpl> download_manager) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  std::unique_ptr<net::URLRequest> url_request =
      DownloadRequestCore::CreateRequestOnIOThread(download_id, params.get());
  std::unique_ptr<storage::BlobDataHandle> blob_data_handle =
      params->GetBlobDataHandle();
  if (blob_data_handle) {
    storage::BlobProtocolHandler::SetRequestedBlobDataHandle(
        url_request.get(), std::move(blob_data_handle));
  }

  if (params->render_process_host_id() >= 0) {
    DownloadInterruptReason reason = DownloadManagerImpl::BeginDownloadRequest(
        std::move(url_request), params->referrer(), resource_context,
        params->content_initiated(), params->render_process_host_id(),
        params->render_view_host_routing_id(),
        params->render_frame_host_routing_id(),
        params->do_not_prompt_for_login());

    if (reason == DOWNLOAD_INTERRUPT_REASON_NONE)
      return nullptr;

    CreateInterruptedDownload(params.get(), reason, download_manager);
    return nullptr;
  }

  return DownloadManagerImpl::UniqueUrlDownloadHandlerPtr(
      UrlDownloader::BeginDownload(download_manager, std::move(url_request),
                                   params->referrer(), false)
          .release());
}
