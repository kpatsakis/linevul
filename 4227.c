void ConflictResolver::IgnoreLocalChanges(MutableEntry* entry) {
  entry->Put(syncable::IS_UNSYNCED, false);
}
