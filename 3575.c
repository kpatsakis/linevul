  void Hold(const SessionStorageNamespaceMap& sessions, int view_route_id) {
    (*session_storage_namespaces_awaiting_close_)[view_route_id] = sessions;
  }
