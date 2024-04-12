void Extension::UpdateTabSpecificPermissions(
    int tab_id,
    scoped_refptr<const PermissionSet> permissions) const {
  base::AutoLock auto_lock(runtime_data_lock_);
  runtime_data_.UpdateTabSpecificPermissions(tab_id, permissions);
}
