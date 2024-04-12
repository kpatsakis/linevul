scoped_refptr<const PermissionSet> PermissionsData::GetTabSpecificPermissions(
    int tab_id) const {
  base::AutoLock auto_lock(runtime_lock_);
  CHECK_GE(tab_id, 0);
  TabPermissionsMap::const_iterator iter =
      tab_specific_permissions_.find(tab_id);
  return (iter != tab_specific_permissions_.end()) ? iter->second : NULL;
}
