void SyncerUtil::CreateNewEntry(syncable::WriteTransaction *trans,
                                const syncable::Id& id) {
  syncable::MutableEntry entry(trans, syncable::GET_BY_ID, id);
  if (!entry.good()) {
    syncable::MutableEntry new_entry(trans, syncable::CREATE_NEW_UPDATE_ITEM,
                                     id);
  }
}
