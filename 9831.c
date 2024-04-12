bool BackendImpl::InitStats() {
  Addr address(data_->header.stats);
  int size = stats_.StorageSize();

  if (!address.is_initialized()) {
    FileType file_type = Addr::RequiredFileType(size);
    DCHECK_NE(file_type, EXTERNAL);
    int num_blocks = Addr::RequiredBlocks(size, file_type);

    if (!CreateBlock(file_type, num_blocks, &address))
      return false;

    data_->header.stats = address.value();
    return stats_.Init(NULL, 0, address);
  }

  if (!address.is_block_file()) {
    NOTREACHED();
    return false;
  }

  size = address.num_blocks() * address.BlockSize();
  MappedFile* file = File(address);
  if (!file)
    return false;

  std::unique_ptr<char[]> data(new char[size]);
  size_t offset = address.start_block() * address.BlockSize() +
                  kBlockHeaderSize;
  if (!file->Read(data.get(), size, offset))
    return false;

  if (!stats_.Init(data.get(), size, address))
    return false;
  if (cache_type_ == net::DISK_CACHE && ShouldReportAgain())
    stats_.InitSizeHistogram();
  return true;
}
