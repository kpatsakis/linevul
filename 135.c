    SyncManager::SyncInternal::HandleTransactionEndingChangeEvent(
        const ImmutableWriteTransactionInfo& write_transaction_info,
        syncable::BaseTransaction* trans) {
  if (!change_delegate_ || ChangeBuffersAreEmpty())
    return ModelTypeSet();

  ReadTransaction read_trans(GetUserShare(), trans);

  ModelTypeSet models_with_changes;
  for (int i = syncable::FIRST_REAL_MODEL_TYPE;
       i < syncable::MODEL_TYPE_COUNT; ++i) {
    const syncable::ModelType type = syncable::ModelTypeFromInt(i);
    if (change_buffers_[type].IsEmpty())
      continue;

    ImmutableChangeRecordList ordered_changes;
    CHECK(change_buffers_[type].GetAllChangesInTreeOrder(&read_trans,
                                                         &ordered_changes));
    if (!ordered_changes.Get().empty()) {
      change_delegate_->
          OnChangesApplied(type, &read_trans, ordered_changes);
      change_observer_.Call(FROM_HERE,
          &SyncManager::ChangeObserver::OnChangesApplied,
          type, write_transaction_info.Get().id, ordered_changes);
      models_with_changes.Put(type);
    }
    change_buffers_[i].Clear();
  }
  return models_with_changes;
}
