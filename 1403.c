bool PermissionsGetAllFunction::RunImpl() {
  scoped_ptr<Permissions> permissions =
      helpers::PackPermissionSet(GetExtension()->GetActivePermissions());
  results_ = GetAll::Results::Create(*permissions);
  return true;
}
