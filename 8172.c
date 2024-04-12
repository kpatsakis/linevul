void WebContentsImpl::AttachToOuterWebContentsFrame(
    WebContents* outer_web_contents,
    RenderFrameHost* outer_contents_frame) {
  CHECK(GuestMode::IsCrossProcessFrameGuest(this));
  RenderFrameHostManager* render_manager = GetRenderManager();

  render_manager->InitRenderView(GetRenderViewHost(), nullptr);
  GetMainFrame()->Init();
  if (!render_manager->GetRenderWidgetHostView())
    CreateRenderWidgetHostViewForRenderManager(GetRenderViewHost());

  auto* outer_web_contents_impl =
      static_cast<WebContentsImpl*>(outer_web_contents);
  auto* outer_contents_frame_impl =
      static_cast<RenderFrameHostImpl*>(outer_contents_frame);
  node_.ConnectToOuterWebContents(outer_web_contents_impl,
                                  outer_contents_frame_impl);

  DCHECK(outer_contents_frame);

  render_manager->CreateOuterDelegateProxy(
      outer_contents_frame->GetSiteInstance(), outer_contents_frame_impl);

  ReattachToOuterWebContentsFrame();

  if (outer_web_contents_impl->frame_tree_.GetFocusedFrame() ==
      outer_contents_frame_impl->frame_tree_node()) {
    SetFocusedFrame(frame_tree_.root(),
                    outer_contents_frame->GetSiteInstance());
  }

  text_input_manager_.reset(nullptr);
}
