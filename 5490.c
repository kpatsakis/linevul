void SyncManager::EnableEncryptEverything() {
  {
    WriteTransaction trans(FROM_HERE, GetUserShare());
    Cryptographer* cryptographer = trans.GetCryptographer();
    if (cryptographer->is_ready())
      cryptographer->set_encrypt_everything();
  }

  data_->EncryptDataTypes(syncable::ModelTypeSet());
}
