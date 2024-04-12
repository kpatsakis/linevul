void SetEntrySpecifics(MutableEntry* meta_entry, SyncEntity* sync_entry) {
  sync_entry->mutable_specifics()->CopyFrom(meta_entry->Get(SPECIFICS));
  sync_entry->set_folder(meta_entry->Get(syncable::IS_DIR));

  DCHECK(meta_entry->GetModelType() == sync_entry->GetModelType());
}
