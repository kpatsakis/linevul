int64_t RenderViewImpl::GetSessionStorageNamespaceId() {
  CHECK(session_storage_namespace_id_ != kInvalidSessionStorageNamespaceId);
  return session_storage_namespace_id_;
}
