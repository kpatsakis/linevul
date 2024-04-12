void NavigationControllerImpl::CopyStateFrom(
    const NavigationController& temp) {
  const NavigationControllerImpl& source =
      static_cast<const NavigationControllerImpl&>(temp);
  DCHECK(GetEntryCount() == 0 && !GetPendingEntry());

  if (source.GetEntryCount() == 0)
    return;  // Nothing new to do.

  needs_reload_ = true;
  InsertEntriesFrom(source, source.GetEntryCount());

  for (SessionStorageNamespaceMap::const_iterator it =
           source.session_storage_namespace_map_.begin();
       it != source.session_storage_namespace_map_.end();
       ++it) {
    SessionStorageNamespaceImpl* source_namespace =
        static_cast<SessionStorageNamespaceImpl*>(it->second.get());
    session_storage_namespace_map_[it->first] = source_namespace->Clone();
  }

  FinishRestore(source.last_committed_entry_index_, RESTORE_CURRENT_SESSION);

  web_contents_->CopyMaxPageIDsFrom(source.web_contents());
}
