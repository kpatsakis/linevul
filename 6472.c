void RunGetFileCallbackHelper(const GetFileCallback& callback,
                              GDataFileError* error,
                              FilePath* file_path,
                              std::string* mime_type,
                              GDataFileType* file_type) {
  DCHECK(error);
  DCHECK(file_path);
  DCHECK(mime_type);
  DCHECK(file_type);

  if (!callback.is_null())
    callback.Run(*error, *file_path, *mime_type, *file_type);
}
