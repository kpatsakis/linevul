bool SyncBackendHost::IsCryptographerReady(
    const sync_api::BaseTransaction* trans) const {
  return initialized() && trans->GetCryptographer()->is_ready();
}
