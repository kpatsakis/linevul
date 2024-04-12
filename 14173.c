void BlobStorageContext::RunOnConstructionBegin(
    const std::string& uuid,
    const BlobStatusCallback& done) {
  BlobEntry* entry = registry_.GetEntry(uuid);
  DCHECK(entry);
  if (entry->status() == BlobStatus::PENDING_CONSTRUCTION) {
    entry->building_state_->build_started_callbacks.push_back(done);
    return;
  }
  done.Run(entry->status());
}
