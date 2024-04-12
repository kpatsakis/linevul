void FileSystemManagerImpl::Create(const GURL& path,
                                   bool exclusive,
                                   bool is_directory,
                                   bool recursive,
                                   CreateCallback callback) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  FileSystemURL url(context_->CrackURL(path));
  base::Optional<base::File::Error> opt_error = ValidateFileSystemURL(url);
  if (opt_error) {
    std::move(callback).Run(opt_error.value());
    return;
  }
  if (!security_policy_->CanCreateFileSystemFile(process_id_, url)) {
    std::move(callback).Run(base::File::FILE_ERROR_SECURITY);
    return;
  }

  if (is_directory) {
    operation_runner()->CreateDirectory(
        url, exclusive, recursive,
        base::BindRepeating(&FileSystemManagerImpl::DidFinish, GetWeakPtr(),
                            base::Passed(&callback)));
  } else {
    operation_runner()->CreateFile(
        url, exclusive,
        base::BindRepeating(&FileSystemManagerImpl::DidFinish, GetWeakPtr(),
                            base::Passed(&callback)));
  }
}
