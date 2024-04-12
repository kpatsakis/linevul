void QuicStreamHost::Initialize(QuicTransportHost* transport_host,
                                P2PQuicStream* p2p_stream) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  DCHECK(transport_host);
  DCHECK(p2p_stream);
  transport_host_ = transport_host;
  p2p_stream_ = p2p_stream;
  p2p_stream_->SetDelegate(this);
}
