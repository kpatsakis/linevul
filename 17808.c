std::unique_ptr<DocumentState> BuildDocumentStateFromParams(
    const CommonNavigationParams& common_params,
    const CommitNavigationParams& commit_params,
    base::TimeTicks time_commit_requested,
    mojom::FrameNavigationControl::CommitNavigationCallback commit_callback,
    mojom::NavigationClient::CommitNavigationCallback
        per_navigation_mojo_interface_commit_callback,
    const network::ResourceResponseHead* head,
    std::unique_ptr<NavigationClient> navigation_client,
    int request_id,
    bool was_initiated_in_this_frame) {
  std::unique_ptr<DocumentState> document_state(new DocumentState());
  InternalDocumentStateData* internal_data =
      InternalDocumentStateData::FromDocumentState(document_state.get());

  DCHECK(!common_params.navigation_start.is_null());
  DCHECK(!common_params.url.SchemeIs(url::kJavaScriptScheme));

  if (common_params.navigation_type == FrameMsg_Navigate_Type::RESTORE) {
    internal_data->set_cache_policy_override(
        blink::mojom::FetchCacheMode::kDefault);
  }

  internal_data->set_is_overriding_user_agent(
      commit_params.is_overriding_user_agent);
  internal_data->set_must_reset_scroll_and_scale_state(
      common_params.navigation_type ==
      FrameMsg_Navigate_Type::RELOAD_ORIGINAL_REQUEST_URL);
  internal_data->set_previews_state(common_params.previews_state);
  internal_data->set_request_id(request_id);
  document_state->set_can_load_local_resources(
      commit_params.can_load_local_resources);

  if (head) {
    if (head->headers)
      internal_data->set_http_status_code(head->headers->response_code());
    else if (common_params.url.SchemeIs(url::kDataScheme))
      internal_data->set_http_status_code(200);
    document_state->set_was_fetched_via_spdy(head->was_fetched_via_spdy);
    document_state->set_was_alpn_negotiated(head->was_alpn_negotiated);
    document_state->set_alpn_negotiated_protocol(
        head->alpn_negotiated_protocol);
    document_state->set_was_alternate_protocol_available(
        head->was_alternate_protocol_available);
    document_state->set_connection_info(head->connection_info);
    internal_data->set_effective_connection_type(
        head->effective_connection_type);
  }

  bool load_data = !common_params.base_url_for_data_url.is_empty() &&
                   !common_params.history_url_for_data_url.is_empty() &&
                   common_params.url.SchemeIs(url::kDataScheme);
  document_state->set_was_load_data_with_base_url_request(load_data);
  if (load_data)
    document_state->set_data_url(common_params.url);

  InternalDocumentStateData::FromDocumentState(document_state.get())
      ->set_navigation_state(NavigationState::CreateBrowserInitiated(
          common_params, commit_params, time_commit_requested,
          std::move(commit_callback),
          std::move(per_navigation_mojo_interface_commit_callback),
          std::move(navigation_client), was_initiated_in_this_frame));
  return document_state;
}
