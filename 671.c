ResourceDispatcherHostImpl::CreateResourceHandlerForDownload(
    net::URLRequest* request,
    bool is_content_initiated,
    bool must_download,
    bool is_new_request) {
  DCHECK(!create_download_handler_intercept_.is_null());
  std::unique_ptr<ResourceHandler> handler =
      create_download_handler_intercept_.Run(request);
  handler =
      HandleDownloadStarted(request, std::move(handler), is_content_initiated,
                            must_download, is_new_request);
  return handler;
}
