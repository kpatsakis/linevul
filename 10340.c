scoped_ptr<ResourceHandler> ResourceDispatcherHostImpl::MaybeInterceptAsStream(
    const base::FilePath& plugin_path,
    net::URLRequest* request,
    ResourceResponse* response,
    std::string* payload) {
  payload->clear();
  ResourceRequestInfoImpl* info = ResourceRequestInfoImpl::ForRequest(request);
  const std::string& mime_type = response->head.mime_type;

  GURL origin;
  if (!delegate_ ||
      !delegate_->ShouldInterceptResourceAsStream(
          request, plugin_path, mime_type, &origin, payload)) {
    return scoped_ptr<ResourceHandler>();
  }

  StreamContext* stream_context =
      GetStreamContextForResourceContext(info->GetContext());

  scoped_ptr<StreamResourceHandler> handler(
      new StreamResourceHandler(request,
                                stream_context->registry(),
                                origin));

  info->set_is_stream(true);
  scoped_ptr<StreamInfo> stream_info(new StreamInfo);
  stream_info->handle = handler->stream()->CreateHandle();
  stream_info->original_url = request->url();
  stream_info->mime_type = mime_type;
  if (response->head.headers.get()) {
    stream_info->response_headers =
        new net::HttpResponseHeaders(response->head.headers->raw_headers());
  }
  delegate_->OnStreamCreated(request, std::move(stream_info));
  return std::move(handler);
}
