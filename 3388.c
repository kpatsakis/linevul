void RenderFrameDevToolsAgentHost::ConnectWebContents(WebContents* wc) {
  RenderFrameHostImpl* host =
      static_cast<RenderFrameHostImpl*>(wc->GetMainFrame());
  DCHECK(host);
  SetFrameTreeNode(host->frame_tree_node());
  UpdateFrameHost(host);
}
