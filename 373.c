bool FrameCompareDepth(RenderFrameHostImpl* a, RenderFrameHostImpl* b) {
  return a->frame_tree_node()->depth() < b->frame_tree_node()->depth();
}
