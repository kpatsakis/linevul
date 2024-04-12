void MetricsWebContentsObserver::OnRequestComplete(
    const GURL& url,
    const net::HostPortPair& host_port_pair,
    int frame_tree_node_id,
    const content::GlobalRequestID& request_id,
    content::RenderFrameHost* render_frame_host_or_null,
    content::ResourceType resource_type,
    bool was_cached,
    std::unique_ptr<data_reduction_proxy::DataReductionProxyData>
        data_reduction_proxy_data,
    int64_t raw_body_bytes,
    int64_t original_content_length,
    base::TimeTicks creation_time,
    int net_error,
    std::unique_ptr<net::LoadTimingInfo> load_timing_info) {
  DCHECK(!base::FeatureList::IsEnabled(network::features::kNetworkService));

  if (!url.SchemeIsHTTPOrHTTPS())
    return;

  PageLoadTracker* tracker = GetTrackerOrNullForRequest(
      request_id, render_frame_host_or_null, resource_type, creation_time);
  if (tracker) {
    ExtraRequestCompleteInfo extra_request_complete_info(
        url, host_port_pair, frame_tree_node_id, was_cached, raw_body_bytes,
        was_cached ? 0 : original_content_length,
        std::move(data_reduction_proxy_data), resource_type, net_error,
        std::move(load_timing_info));
    tracker->OnLoadedResource(extra_request_complete_info);
  }
}
