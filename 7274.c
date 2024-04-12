void ExpectChildFrameSetAsCollapsedInFTN(Shell* shell, bool expect_collapsed) {
  FrameTreeNode* root = static_cast<WebContentsImpl*>(shell->web_contents())
                            ->GetFrameTree()
                            ->root();
  ASSERT_EQ(1u, root->child_count());
  FrameTreeNode* child = root->child_at(0u);
  EXPECT_EQ(expect_collapsed, child->is_collapsed());
}
