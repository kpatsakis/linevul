IndexedDBTransaction* IndexedDBDatabase::CreateTransaction(
    int64_t transaction_id,
    IndexedDBConnection* connection,
    const std::vector<int64_t>& object_store_ids,
    blink::WebIDBTransactionMode mode) {
  IDB_TRACE1("IndexedDBDatabase::CreateTransaction", "txn.id", transaction_id);
  DCHECK(connections_.count(connection));

  UMA_HISTOGRAM_COUNTS_1000(
      "WebCore.IndexedDB.Database.OutstandingTransactionCount",
      transaction_count_);

  IndexedDBTransaction* transaction = connection->CreateTransaction(
      transaction_id,
      std::set<int64_t>(object_store_ids.begin(), object_store_ids.end()), mode,
      new IndexedDBBackingStore::Transaction(backing_store_.get()));
  TransactionCreated(transaction);
  return transaction;
}
