bool RenderFrameHostImpl::CanCommitURL(const GURL& url) {
  if (IsRendererDebugURL(url))
    return false;


  if (!frame_tree_node()->IsMainFrame()) {
    bool is_in_mhtml = frame_tree_node_->frame_tree()
                           ->root()
                           ->current_frame_host()
                           ->is_mhtml_document();
    if (is_in_mhtml) {
      return IsSameSiteInstance(
          frame_tree_node()->parent()->current_frame_host());
    }
  }

  if (!GetContentClient()->browser()->CanCommitURL(GetProcess(), url))
    return false;


  return true;
}
