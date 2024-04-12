bool BookmarksGetFunction::RunImpl() {
  scoped_ptr<bookmarks::GetRecent::Params> params(
      bookmarks::GetRecent::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());
  if (params->number_of_items < 1)
    return false;

  std::vector<const BookmarkNode*> nodes;
  bookmark_utils::GetMostRecentlyAddedEntries(
      BookmarkModelFactory::GetForProfile(profile()),
      params->number_of_items,
      &nodes);

  std::vector<linked_ptr<BookmarkTreeNode> > tree_nodes;
  std::vector<const BookmarkNode*>::iterator i = nodes.begin();
  for (; i != nodes.end(); ++i) {
    const BookmarkNode* node = *i;
    bookmark_api_helpers::AddNode(node, &tree_nodes, false);
  }

  results_ = bookmarks::GetRecent::Results::Create(tree_nodes);
  return true;
}
