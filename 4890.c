bool ChildProcessSecurityPolicyImpl::CanCreateReadWriteFileSystemFile(
    int child_id,
    const storage::FileSystemURL& url) {
  return HasPermissionsForFileSystemFile(child_id, url,
                                         CREATE_READ_WRITE_FILE_GRANT);
}
