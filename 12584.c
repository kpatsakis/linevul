void GetErrorQuery::Destroy(bool /* have_context */) {
  if (!IsDeleted()) {
    MarkAsDeleted();
  }
}
