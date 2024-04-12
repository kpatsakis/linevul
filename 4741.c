void GetLocalFileInfoOnBlockingPool(
    const FilePath& local_file,
    GDataFileError* error,
    int64* file_size,
    std::string* content_type) {
  DCHECK(error);
  DCHECK(file_size);
  DCHECK(content_type);

  if (!net::GetMimeTypeFromExtension(local_file.Extension(), content_type))
    *content_type = kMimeTypeOctetStream;

  *file_size = 0;
  *error = file_util::GetFileSize(local_file, file_size) ?
      GDATA_FILE_OK :
      GDATA_FILE_ERROR_NOT_FOUND;
}
