bool BookmarksCreateFunction::RunImpl() {
  if (!EditBookmarksEnabled())
    return false;

  scoped_ptr<bookmarks::Create::Params> params(
      bookmarks::Create::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params.get());

  BookmarkModel* model = BookmarkModelFactory::GetForProfile(profile());
  int64 parentId;

  if (!params->bookmark.parent_id.get()) {
    parentId = model->other_node()->id();
  } else {
    if (!GetBookmarkIdAsInt64(*params->bookmark.parent_id, &parentId))
      return false;
  }
  const BookmarkNode* parent = model->GetNodeByID(parentId);
  if (!parent) {
    error_ = keys::kNoParentError;
    return false;
  }
  if (parent->is_root()) {  // Can't create children of the root.
    error_ = keys::kModifySpecialError;
    return false;
  }

  int index;
  if (!params->bookmark.index.get()) {  // Optional (defaults to end).
    index = parent->child_count();
  } else {
    index = *params->bookmark.index;
    if (index > parent->child_count() || index < 0) {
      error_ = keys::kInvalidIndexError;
      return false;
    }
  }

  string16 title;  // Optional.
  if (params->bookmark.title.get())
    title = UTF8ToUTF16(*params->bookmark.title.get());

  std::string url_string;  // Optional.
  if (params->bookmark.url.get())
    url_string = *params->bookmark.url.get();

  GURL url(url_string);
  if (!url_string.empty() && !url.is_valid()) {
    error_ = keys::kInvalidUrlError;
    return false;
  }

  const BookmarkNode* node;
  if (url_string.length())
    node = model->AddURL(parent, index, title, url);
  else
    node = model->AddFolder(parent, index, title);
  DCHECK(node);
  if (!node) {
    error_ = keys::kNoNodeError;
    return false;
  }

  scoped_ptr<BookmarkTreeNode> ret(
      bookmark_api_helpers::GetBookmarkTreeNode(node, false, false));
  results_ = bookmarks::Create::Results::Create(*ret);

  return true;
}
