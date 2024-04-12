WebContentsImpl::WebContentsTreeNode::WebContentsTreeNode(
    WebContentsImpl* current_web_contents)
    : current_web_contents_(current_web_contents),
      outer_web_contents_(nullptr),
      outer_contents_frame_tree_node_id_(
          FrameTreeNode::kFrameTreeNodeInvalidId),
      focused_web_contents_(current_web_contents) {}
