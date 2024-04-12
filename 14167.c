void OSExchangeDataProviderWin::SetFileContents(
    const base::FilePath& filename,
    const std::string& file_contents) {
  STGMEDIUM* storage = GetStorageForFileDescriptor(filename);
  data_->contents_.push_back(new DataObjectImpl::StoredDataInfo(
      Clipboard::GetFileDescriptorFormatType().ToFormatEtc(), storage));

  storage = GetStorageForBytes(file_contents.data(), file_contents.length());
  data_->contents_.push_back(new DataObjectImpl::StoredDataInfo(
      Clipboard::GetFileContentZeroFormatType().ToFormatEtc(), storage));
}
