ResourceDispatcherHostImpl::GetInterestingPerFrameLoadInfos() {
  auto infos = std::make_unique<LoadInfoList>();
  std::map<GlobalFrameRoutingId, LoadInfo> frame_infos;
  for (const auto& loader : pending_loaders_) {
    net::URLRequest* request = loader.second->request();
    net::UploadProgress upload_progress = request->GetUploadProgress();

    LoadInfo load_info;
    load_info.host = request->url().host();
    load_info.load_state = request->GetLoadState();
    load_info.upload_size = upload_progress.size();
    load_info.upload_position = upload_progress.position();

    ResourceRequestInfoImpl* request_info = loader.second->GetRequestInfo();
    load_info.web_contents_getter =
        request_info->GetWebContentsGetterForRequest();

    if (request_info->frame_tree_node_id() != -1) {
      infos->push_back(load_info);
    } else {
      GlobalFrameRoutingId id(request_info->GetChildID(),
                              request_info->GetRenderFrameID());
      auto existing = frame_infos.find(id);
      if (existing == frame_infos.end() ||
          LoadInfoIsMoreInteresting(load_info, existing->second)) {
        frame_infos[id] = std::move(load_info);
      }
    }
  }

  for (auto it : frame_infos) {
    infos->push_back(std::move(it.second));
  }
  return infos;
}
