bool PermissionsData::HasAPIPermissionForTab(
    int tab_id,
    APIPermission::ID permission) const {
  if (HasAPIPermission(permission))
    return true;

  scoped_refptr<const PermissionSet> tab_permissions =
      GetTabSpecificPermissions(tab_id);

  base::AutoLock auto_lock(runtime_lock_);
  return tab_permissions.get() && tab_permissions->HasAPIPermission(permission);
}
