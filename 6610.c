  void SetStreamAndDelegate(
      P2PQuicStreamImpl* stream,
      std::unique_ptr<MockP2PQuicStreamDelegate> stream_delegate) {
    DCHECK(stream);
    stream_ = stream;
    stream_id_ = stream->id();
    stream_delegate_ = std::move(stream_delegate);
  }
