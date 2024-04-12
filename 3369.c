void ExtensionWebContentsObserver::OnRequest(
    content::RenderFrameHost* render_frame_host,
    const ExtensionHostMsg_Request_Params& params) {
  dispatcher_.Dispatch(params, render_frame_host);
}
