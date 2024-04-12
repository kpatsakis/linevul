  bool MaybeCreateLoaderForResponse(
      const network::ResourceResponseHead& response) {
    if (!IsLoaderInterceptionEnabled())
      return false;

    if (!default_loader_used_)
      return false;

    for (auto& interceptor : interceptors_) {
      network::mojom::URLLoaderClientRequest response_client_request;
      if (interceptor->MaybeCreateLoaderForResponse(
              response, &response_url_loader_, &response_client_request,
              url_loader_.get())) {
        if (response_loader_binding_.is_bound())
          response_loader_binding_.Close();
        response_loader_binding_.Bind(std::move(response_client_request));
        default_loader_used_ = false;
        url_loader_.reset();
        return true;
      }
    }
    return false;
  }
