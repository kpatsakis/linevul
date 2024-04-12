ChromeExtensionsAPIClient::GetNonNativeFileSystemDelegate() {
  if (!non_native_file_system_delegate_) {
    non_native_file_system_delegate_ =
        base::MakeUnique<NonNativeFileSystemDelegateChromeOS>();
  }
  return non_native_file_system_delegate_.get();
}
