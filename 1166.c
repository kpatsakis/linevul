  void Initialize() {
    buffer_.reset(new QuicStreamSequencerBuffer(max_capacity_bytes_));
    helper_.reset(new QuicStreamSequencerBufferPeer(buffer_.get()));
  }
