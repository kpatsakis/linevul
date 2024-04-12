  void DidGetModifiedSince(QuotaManager* manager,
                           const GetOriginsCallback& callback,
                           StorageType type,
                           bool success) {
    if (!manager) {
      callback.Run(std::set<GURL>(), type);
      return;
    }
    manager->DidDatabaseWork(success);
    callback.Run(origins_, type);
  }
