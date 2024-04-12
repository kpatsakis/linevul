syncable::ModelTypeSet ProfileSyncService::GetEncryptedDataTypes() const {
  DCHECK(encrypted_types_.Has(syncable::PASSWORDS));
  return encrypted_types_;
}
