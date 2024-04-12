bool PermissionsData::HasAPIPermission(APIPermission::ID permission) const {
  return active_permissions()->HasAPIPermission(permission);
}
