void IndexedDBConnection::ForceClose() {
  if (!callbacks_.get())
    return;

  base::WeakPtr<IndexedDBConnection> this_obj = weak_factory_.GetWeakPtr();
  scoped_refptr<IndexedDBDatabaseCallbacks> callbacks(callbacks_);
  database_->Close(this, true /* forced */);
  if (this_obj) {
    database_ = nullptr;
    callbacks_ = nullptr;
    active_observers_.clear();
  }
  callbacks->OnForcedClose();
}
