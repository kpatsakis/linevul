WebStorageNamespace* RenderViewImpl::createSessionStorageNamespace(
    unsigned quota) {
  CHECK(session_storage_namespace_id_ !=
        dom_storage::kInvalidSessionStorageNamespaceId);
  return new WebStorageNamespaceImpl(session_storage_namespace_id_);
}
