  void StartUpgrade() {
    connection_ = db_->CreateConnection(pending_->database_callbacks,
                                        pending_->child_process_id);
    DCHECK_EQ(db_->connections_.count(connection_.get()), 1UL);

    std::vector<int64_t> object_store_ids;
    IndexedDBTransaction* transaction = db_->CreateTransaction(
        pending_->transaction_id, connection_.get(), object_store_ids,
        blink::kWebIDBTransactionModeVersionChange);

    DCHECK(db_->transaction_coordinator_.IsRunningVersionChangeTransaction());
    transaction->ScheduleTask(
        base::BindOnce(&IndexedDBDatabase::VersionChangeOperation, db_,
                       pending_->version, pending_->callbacks));
  }
