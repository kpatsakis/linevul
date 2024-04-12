TestWebKitPlatformSupport::databaseOpenFile(
    const WebKit::WebString& vfs_file_name, int desired_flags) {
  return SimpleDatabaseSystem::GetInstance()->OpenFile(
      vfs_file_name, desired_flags);
}
