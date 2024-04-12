void TestingAutomationProvider::ReparentBookmark(int handle,
                                                 int64 id,
                                                 int64 new_parent_id,
                                                 int index,
                                                 bool* success) {
  if (browser_tracker_->ContainsHandle(handle)) {
    Browser* browser = browser_tracker_->GetResource(handle);
    if (browser) {
      BookmarkModel* model = browser->profile()->GetBookmarkModel();
      if (!model->IsLoaded()) {
        *success = false;
        return;
      }
      const BookmarkNode* node = model->GetNodeByID(id);
      DCHECK(node);
      const BookmarkNode* new_parent = model->GetNodeByID(new_parent_id);
      DCHECK(new_parent);
      if (node && new_parent) {
        model->Move(node, new_parent, index);
        *success = true;
      }
    }
  }
  *success = false;
}
