void RenderFrameHostImpl::EnterBackForwardCache() {
  DCHECK(IsBackForwardCacheEnabled());
  DCHECK(!is_in_back_forward_cache_);
  is_in_back_forward_cache_ = true;
  for (auto& child : children_)
    child->current_frame_host()->EnterBackForwardCache();
}
