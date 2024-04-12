quic::QuicCryptoStream* P2PQuicTransportImpl::GetMutableCryptoStream() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  return crypto_stream_.get();
}
