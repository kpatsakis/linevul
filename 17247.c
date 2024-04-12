  FileChooserImpl(RenderFrameHostImpl* render_frame_host)
      : render_frame_host_(render_frame_host) {
    Observe(WebContents::FromRenderFrameHost(render_frame_host));
  }
