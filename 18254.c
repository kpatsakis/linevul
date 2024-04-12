 std::unique_ptr<media::CdmAllocator> CreateCdmAllocator() {
  return base::MakeUnique<media::MojoCdmAllocator>();
}
