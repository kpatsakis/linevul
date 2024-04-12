bool ChildProcessSecurityPolicyImpl::CanCreateFileSystemFile(
    int child_id,
    const storage::FileSystemURL& url) {
  return HasPermissionsForFileSystemFile(child_id, url, CREATE_NEW_FILE_GRANT);
}
