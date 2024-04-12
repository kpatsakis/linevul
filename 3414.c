void SyncBackendHost::Core::OnEncryptedTypesChanged(
    syncable::ModelTypeSet encrypted_types,
    bool encrypt_everything) {
  if (!sync_loop_)
    return;
  DCHECK_EQ(MessageLoop::current(), sync_loop_);
  host_.Call(
      FROM_HERE,
      &SyncBackendHost::NotifyEncryptedTypesChanged,
      encrypted_types, encrypt_everything);
}
