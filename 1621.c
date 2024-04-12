void IndexedDBDatabase::ReportErrorWithDetails(Status status,
                                               const char* message) {
  DCHECK(!status.ok());
  if (status.IsCorruption()) {
    IndexedDBDatabaseError error(blink::kWebIDBDatabaseExceptionUnknownError,
                                 message);
    factory_->HandleBackingStoreCorruption(backing_store_->origin(), error);
  } else {
    factory_->HandleBackingStoreFailure(backing_store_->origin());
  }
}
