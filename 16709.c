void SyncBackendHost::EncryptDataTypes(
    const syncable::ModelTypeSet& encrypted_types) {
  core_thread_.message_loop()->PostTask(FROM_HERE,
     NewRunnableMethod(core_.get(),
                       &SyncBackendHost::Core::DoEncryptDataTypes,
                       encrypted_types));
}
