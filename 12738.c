  void GrantPermissionsForFile(const base::FilePath& file, int permissions) {
    base::FilePath stripped = file.StripTrailingSeparators();
    file_permissions_[stripped] |= permissions;
    UMA_HISTOGRAM_COUNTS_1M(
        "ChildProcessSecurityPolicy.FilePermissionPathLength",
        stripped.value().size());
  }
