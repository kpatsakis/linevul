int64 MakeNode(UserShare* share,
               ModelType model_type,
               const std::string& client_tag) {
  WriteTransaction trans(FROM_HERE, share);
  ReadNode root_node(&trans);
  root_node.InitByRootLookup();
  WriteNode node(&trans);
  sync_api::WriteNode::InitUniqueByCreationResult result =
      node.InitUniqueByCreation(model_type, root_node, client_tag);
  EXPECT_EQ(sync_api::WriteNode::INIT_SUCCESS, result);
  node.SetIsFolder(false);
  return node.GetId();
}
