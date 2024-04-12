void FileSystemManagerImpl::Write(
    const GURL& file_path,
    const std::string& blob_uuid,
    int64_t position,
    blink::mojom::FileSystemCancellableOperationRequest op_request,
    blink::mojom::FileSystemOperationListenerPtr listener) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  FileSystemURL url(context_->CrackURL(file_path));
  base::Optional<base::File::Error> opt_error = ValidateFileSystemURL(url);
  if (opt_error) {
    listener->ErrorOccurred(opt_error.value());
    return;
  }
  if (!security_policy_->CanWriteFileSystemFile(process_id_, url)) {
    listener->ErrorOccurred(base::File::FILE_ERROR_SECURITY);
    return;
  }
  std::unique_ptr<storage::BlobDataHandle> blob =
      blob_storage_context_->context()->GetBlobDataFromUUID(blob_uuid);

  OperationListenerID listener_id = AddOpListener(std::move(listener));

  OperationID op_id = operation_runner()->Write(
      url, std::move(blob), position,
      base::BindRepeating(&FileSystemManagerImpl::DidWrite, GetWeakPtr(),
                          listener_id));
  cancellable_operations_.AddBinding(
      std::make_unique<FileSystemCancellableOperationImpl>(op_id, this),
      std::move(op_request));
}
