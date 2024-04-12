  void CallOnReceivedResponse(
      const network::ResourceResponseHead& head,
      network::mojom::URLLoaderClientEndpointsPtr url_loader_client_endpoints,
      std::unique_ptr<NavigationData> cloned_navigation_data,
      bool is_download,
      bool is_stream,
      PreviewsState previews_state) {
    scoped_refptr<network::ResourceResponse> response(
        new network::ResourceResponse());
    response->head = head;

    base::PostTaskWithTraits(
        FROM_HERE, {BrowserThread::UI},
        base::BindOnce(&NavigationURLLoaderImpl::OnReceiveResponse, owner_,
                       response->DeepCopy(),
                       std::move(url_loader_client_endpoints),
                       std::move(cloned_navigation_data), global_request_id_,
                       is_download, is_stream, previews_state));
  }
