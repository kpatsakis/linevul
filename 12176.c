void WebContentsImpl::DidNavigateMainFramePostCommit(
    RenderFrameHostImpl* render_frame_host,
    const LoadCommittedDetails& details,
    const FrameHostMsg_DidCommitProvisionalLoad_Params& params) {
  if (details.is_navigation_to_different_page()) {
    UpdateTargetURL(render_frame_host->GetRenderViewHost(), GURL());

    RenderWidgetHostViewBase* rwhvb =
        static_cast<RenderWidgetHostViewBase*>(GetRenderWidgetHostView());
    if (rwhvb)
      rwhvb->OnDidNavigateMainFrameToNewPage();

    did_first_visually_non_empty_paint_ = false;

    theme_color_ = SK_ColorTRANSPARENT;
  }

  if (delegate_)
    delegate_->DidNavigateMainFramePostCommit(this);
  view_->SetOverscrollControllerEnabled(CanOverscrollContent());
}
