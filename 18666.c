void InFlightBackendIO::CloseEntryImpl(EntryImpl* entry) {
  scoped_refptr<BackendIO> operation(
      new BackendIO(this, backend_, net::CompletionCallback()));
  operation->CloseEntryImpl(entry);
  PostOperation(FROM_HERE, operation.get());
}
