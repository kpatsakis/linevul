WebContentsImpl::GetRenderWidgetHostViewsInTree() {
  std::set<RenderWidgetHostView*> set;
  if (ShowingInterstitialPage()) {
    if (RenderWidgetHostView* rwhv = GetRenderWidgetHostView())
      set.insert(rwhv);
  } else {
    for (RenderFrameHost* rfh : GetAllFrames()) {
      if (RenderWidgetHostView* rwhv = static_cast<RenderFrameHostImpl*>(rfh)
                                           ->frame_tree_node()
                                           ->render_manager()
                                           ->GetRenderWidgetHostView()) {
        set.insert(rwhv);
      }
    }
  }
  return set;
}
