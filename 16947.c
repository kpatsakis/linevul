  void InitResource(SafeBrowsingService::UnsafeResource* resource,
                    bool is_subresource,
                    const GURL& url) {
    resource->client = this;
    resource->url = url;
    resource->is_subresource = is_subresource;
    resource->threat_type = SafeBrowsingService::URL_MALWARE;
    resource->render_process_host_id = contents()->GetRenderProcessHost()->
        GetID();
    resource->render_view_id = contents()->render_view_host()->routing_id();
  }
