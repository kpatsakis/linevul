void BackendImpl::StoreStats() {
  int size = stats_.StorageSize();
  std::unique_ptr<char[]> data(new char[size]);
  Addr address;
  size = stats_.SerializeStats(data.get(), size, &address);
  DCHECK(size);
  if (!address.is_initialized())
    return;

  MappedFile* file = File(address);
  if (!file)
    return;

  size_t offset = address.start_block() * address.BlockSize() +
                  kBlockHeaderSize;
  file->Write(data.get(), size, offset);  // ignore result.
}
