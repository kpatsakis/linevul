void DefaultTabHandler::TabReplacedAt(TabStripModel* tab_strip_model,
                                      TabContentsWrapper* old_contents,
                                      TabContentsWrapper* new_contents,
                                      int index) {
  delegate_->AsBrowser()->TabReplacedAt(tab_strip_model, old_contents,
                                        new_contents, index);
}
