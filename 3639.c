void BlobStorageContext::RunOnConstructionComplete(
    const std::string& uuid,
    const BlobStatusCallback& done) {
  BlobEntry* entry = registry_.GetEntry(uuid);
  DCHECK(entry);
  if (BlobStatusIsPending(entry->status())) {
    entry->building_state_->build_completion_callbacks.push_back(done);
    return;
  }
  done.Run(entry->status());
}
