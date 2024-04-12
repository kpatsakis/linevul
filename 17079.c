void PageInfoBubbleView::RenderFrameDeleted(
    content::RenderFrameHost* render_frame_host) {
  if (render_frame_host == web_contents()->GetMainFrame()) {
    GetWidget()->Close();
  }
}
