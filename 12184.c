DOMStorageContextWrapper::RecreateSessionStorage(
    const std::string& namespace_id) {
  return SessionStorageNamespaceImpl::Create(this, namespace_id);
}
