void SyncManager::SyncInternal::BootstrapEncryption(
    const std::string& restored_key_for_bootstrapping) {
  ReadTransaction trans(FROM_HERE, GetUserShare());
  Cryptographer* cryptographer = trans.GetCryptographer();

  cryptographer->Bootstrap(restored_key_for_bootstrapping);
}
