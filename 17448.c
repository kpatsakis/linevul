void RenderFrameHostManager::CreateProxiesForNewRenderFrameHost(
    SiteInstance* old_instance,
    SiteInstance* new_instance) {
  if (new_instance->IsRelatedSiteInstance(old_instance)) {
    CreateOpenerProxies(new_instance, frame_tree_node_);
  } else {
    frame_tree_node_->frame_tree()->CreateProxiesForSiteInstance(
        frame_tree_node_, new_instance);
  }
}
