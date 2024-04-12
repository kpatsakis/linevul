void RenderFrameHostImpl::RequestAXTreeSnapshot(AXTreeSnapshotCallback callback,
                                                ui::AXMode ax_mode) {
  static int next_id = 1;
  int callback_id = next_id++;
  Send(new AccessibilityMsg_SnapshotTree(routing_id_, callback_id,
                                         ax_mode.mode()));
  ax_tree_snapshot_callbacks_.insert(
      std::make_pair(callback_id, std::move(callback)));
}
