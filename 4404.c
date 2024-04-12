PermissionMessages Extension::GetPermissionMessages() const {
  base::AutoLock auto_lock(runtime_data_lock_);
  if (IsTrustedId(id())) {
    return PermissionMessages();
  } else {
    return runtime_data_.GetActivePermissions()->GetPermissionMessages(
        GetType());
  }
}
