bool QuicStreamSequencerBuffer::RetireBlock(size_t idx) {
  if (blocks_[idx] == nullptr) {
    QUIC_BUG << "Try to retire block twice";
    return false;
  }
  delete blocks_[idx];
  blocks_[idx] = nullptr;
  QUIC_DVLOG(1) << "Retired block with index: " << idx;
  return true;
}
