void SyncBackendHost::Core::OnChangesComplete(
    syncable::ModelType model_type) {
  if (!host_ || !host_->frontend_) {
    DCHECK(false) << "OnChangesComplete called after Shutdown?";
    return;
  }

  ChangeProcessor* processor = GetProcessor(model_type);
  if (!processor)
    return;

  processor->CommitChangesFromSyncModel();
}
