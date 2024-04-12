bool ExecuteCodeInTabFunction::HasPermission() {
  if (Init() == SUCCESS &&
      extension_->permissions_data()->HasAPIPermissionForTab(
          execute_tab_id_, APIPermission::kTab)) {
    return true;
  }
  return ExtensionFunction::HasPermission();
}
