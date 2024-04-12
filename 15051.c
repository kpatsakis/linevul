ResourceRequestInfoImpl* ResourceDispatcherHostImpl::CreateRequestInfo(
    ResourceHandler* handler,
    int child_id,
    int route_id,
    bool download,
    ResourceContext* context) {
  return new ResourceRequestInfoImpl(
      handler,
      PROCESS_TYPE_RENDERER,
      child_id,
      route_id,
      0,
      request_id_,
      false,     // is_main_frame
      -1,        // frame_id
      false,     // parent_is_main_frame
      -1,        // parent_frame_id
      ResourceType::SUB_RESOURCE,
      PAGE_TRANSITION_LINK,
      0,         // upload_size
      download,  // is_download
      download,  // allow_download
      false,     // has_user_gesture
      WebKit::WebReferrerPolicyDefault,
      context);
}
