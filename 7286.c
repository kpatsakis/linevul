void SyncBackendHost::Core::SaveChanges() {
  DCHECK_EQ(MessageLoop::current(), sync_loop_);
  sync_manager_->SaveChanges();
}
