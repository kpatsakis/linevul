bool SyncManager::SyncInternal::IsUsingExplicitPassphrase() {
  ReadTransaction trans(FROM_HERE, &share_);
  ReadNode node(&trans);
  if (node.InitByTagLookup(kNigoriTag) != sync_api::BaseNode::INIT_OK) {
    NOTREACHED();
    return false;
  }

  return node.GetNigoriSpecifics().using_explicit_passphrase();
}
