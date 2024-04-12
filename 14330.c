PermissionsData::AccessType PermissionsData::GetPageAccess(
    const Extension* extension,
    const GURL& document_url,
    int tab_id,
    std::string* error) const {
  base::AutoLock auto_lock(runtime_lock_);

  const PermissionSet* tab_permissions = GetTabSpecificPermissions(tab_id);
  return CanRunOnPage(
      extension, document_url, tab_id,
      active_permissions_unsafe_->explicit_hosts(),
      withheld_permissions_unsafe_->explicit_hosts(),
      tab_permissions ? &tab_permissions->explicit_hosts() : nullptr, error);
}
