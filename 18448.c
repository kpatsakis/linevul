void SyncManager::SyncInternal::SetExtraChangeRecordData(int64 id,
    syncable::ModelType type, ChangeReorderBuffer* buffer,
    Cryptographer* cryptographer, const syncable::EntryKernel& original,
    bool existed_before, bool exists_now) {
  if (!exists_now && existed_before) {
    sync_pb::EntitySpecifics original_specifics(original.ref(SPECIFICS));
    if (type == syncable::PASSWORDS) {
      scoped_ptr<sync_pb::PasswordSpecificsData> data(
          DecryptPasswordSpecifics(original_specifics, cryptographer));
      if (!data.get()) {
        NOTREACHED();
        return;
      }
      buffer->SetExtraDataForId(id, new ExtraPasswordChangeRecordData(*data));
    } else if (original_specifics.has_encrypted()) {
      const sync_pb::EncryptedData& encrypted = original_specifics.encrypted();
      if (!cryptographer->Decrypt(encrypted, &original_specifics)) {
        NOTREACHED();
        return;
      }
    }
    buffer->SetSpecificsForId(id, original_specifics);
  }
}
