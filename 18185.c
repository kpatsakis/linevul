void DefaultTabHandler::TabDetachedAt(TabContentsWrapper* contents, int index) {
  delegate_->AsBrowser()->TabDetachedAt(contents, index);
}
