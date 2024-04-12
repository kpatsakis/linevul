  bool CurrentFullscreenFrameTreeNodeIsEmpty() {
    WebContentsImpl* web_contents =
        static_cast<WebContentsImpl*>(shell()->web_contents());
    return web_contents->current_fullscreen_frame_tree_node_id_ ==
           RenderFrameHost::kNoFrameTreeNodeId;
  }
