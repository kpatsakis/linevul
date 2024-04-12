void ExpectChildFrameCollapsed(Shell* shell,
                               const std::string& frame_id,
                               bool expect_collapsed) {
  ExpectChildFrameSetAsCollapsedInFTN(shell, expect_collapsed);
  ExpectChildFrameCollapsedInLayout(shell, frame_id, expect_collapsed);
}
