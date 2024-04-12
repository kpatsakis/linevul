void DevToolsUIBindings::FileSystemAdded(
    const DevToolsFileHelper::FileSystem& file_system) {
  std::unique_ptr<base::DictionaryValue> file_system_value(
      CreateFileSystemValue(file_system));
  CallClientFunction("DevToolsAPI.fileSystemAdded",
                     file_system_value.get(), NULL, NULL);
}
