bool SyncerUtil::ServerAndLocalOrdersMatch(syncable::Entry* entry) {
  syncable::Id local_up_to_date_predecessor = entry->Get(PREV_ID);
  while (!local_up_to_date_predecessor.IsRoot()) {
    Entry local_prev(entry->trans(), GET_BY_ID, local_up_to_date_predecessor);
    if (!local_prev.good() || local_prev.Get(IS_DEL))
      return false;
    if (!local_prev.Get(IS_UNAPPLIED_UPDATE) && !local_prev.Get(IS_UNSYNCED))
      break;
    local_up_to_date_predecessor = local_prev.Get(PREV_ID);
  }

  syncable::Id server_up_to_date_predecessor =
      entry->ComputePrevIdFromServerPosition(entry->Get(SERVER_PARENT_ID));
  return server_up_to_date_predecessor == local_up_to_date_predecessor;
}
