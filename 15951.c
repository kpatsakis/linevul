std::vector<string16> Extension::GetPermissionMessageStrings() const {
  base::AutoLock auto_lock(runtime_data_lock_);
  if (IsTrustedId(id()))
    return std::vector<string16>();
  else
    return runtime_data_.GetActivePermissions()->GetWarningMessages(GetType());
}
