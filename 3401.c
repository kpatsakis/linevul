void GDataFileSystem::OnGetFileFromCache(const GetFileFromCacheParams& params,
                                         GDataFileError error,
                                         const std::string& resource_id,
                                         const std::string& md5,
                                         const FilePath& cache_file_path) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  if (error == GDATA_FILE_OK) {
    if (!params.get_file_callback.is_null()) {
      params.get_file_callback.Run(error,
                                   cache_file_path,
                                   params.mime_type,
                                   REGULAR_FILE);
    }
    return;
  }

  documents_service_->GetDocumentEntry(
      resource_id,
      base::Bind(&GDataFileSystem::OnGetDocumentEntry,
                 ui_weak_ptr_,
                 cache_file_path,
                 GetFileFromCacheParams(params.virtual_file_path,
                                        params.local_tmp_path,
                                        params.content_url,
                                        params.resource_id,
                                        params.md5,
                                        params.mime_type,
                                        params.get_file_callback,
                                        params.get_download_data_callback)));
}
