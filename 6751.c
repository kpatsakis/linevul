void TestingAutomationProvider::WaitForBookmarkModelToLoad(
    int handle,
    IPC::Message* reply_message) {
  if (browser_tracker_->ContainsHandle(handle)) {
    Browser* browser = browser_tracker_->GetResource(handle);
    BookmarkModel* model = browser->profile()->GetBookmarkModel();
    if (model->IsLoaded()) {
      AutomationMsg_WaitForBookmarkModelToLoad::WriteReplyParams(
          reply_message, true);
      Send(reply_message);
    } else {
      new AutomationProviderBookmarkModelObserver(this, reply_message,
                                                  model);
    }
  }
}
