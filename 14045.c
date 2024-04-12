void DocumentLoader::SetHistoryItemStateForCommit(
    HistoryItem* old_item,
    WebFrameLoadType load_type,
    HistoryNavigationType navigation_type) {
  if (!history_item_ || !IsBackForwardLoadType(load_type))
    history_item_ = HistoryItem::Create();

  history_item_->SetURL(UrlForHistory());
  history_item_->SetReferrer(SecurityPolicy::GenerateReferrer(
      request_.GetReferrerPolicy(), history_item_->Url(),
      request_.HttpReferrer()));
  history_item_->SetFormInfoFromRequest(request_);

  if (!old_item || IsBackForwardLoadType(load_type))
    return;
  WebHistoryCommitType history_commit_type = LoadTypeToCommitType(load_type);
  if (navigation_type == HistoryNavigationType::kDifferentDocument &&
      (history_commit_type != kWebHistoryInertCommit ||
       !EqualIgnoringFragmentIdentifier(old_item->Url(), history_item_->Url())))
    return;
  history_item_->SetDocumentSequenceNumber(old_item->DocumentSequenceNumber());

  history_item_->CopyViewStateFrom(old_item);
  history_item_->SetScrollRestorationType(old_item->ScrollRestorationType());

  if (history_commit_type == kWebHistoryInertCommit &&
      (navigation_type == HistoryNavigationType::kHistoryApi ||
       old_item->Url() == history_item_->Url())) {
    history_item_->SetStateObject(old_item->StateObject());
    history_item_->SetItemSequenceNumber(old_item->ItemSequenceNumber());
  }
}
