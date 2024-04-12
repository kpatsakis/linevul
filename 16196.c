void GDataCacheMetadata::AssertOnSequencedWorkerPool() {
  DCHECK(!pool_ || pool_->IsRunningSequenceOnCurrentThread(sequence_token_));
}
