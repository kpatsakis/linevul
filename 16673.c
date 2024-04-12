void ChildProcessSecurityPolicyImpl::GrantCreateReadWriteFileSystem(
    int child_id, const std::string& filesystem_id) {
  GrantPermissionsForFileSystem(
      child_id, filesystem_id, CREATE_READ_WRITE_FILE_GRANT);
}
