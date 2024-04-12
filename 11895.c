bool BitReaderCore::SkipBits(int num_bits) {
  DCHECK_GE(num_bits, 0);

  const int remaining_bits = nbits_ + nbits_next_;
  if (remaining_bits >= num_bits)
    return SkipBitsSmall(num_bits);

  num_bits -= remaining_bits;
  bits_read_ += remaining_bits;
  nbits_ = 0;
  reg_ = 0;
  nbits_next_ = 0;
  reg_next_ = 0;

  const int nbytes = num_bits / 8;
  if (nbytes > 0) {
    const uint8_t* byte_stream_window;
    const int window_size =
        byte_stream_provider_->GetBytes(nbytes, &byte_stream_window);
    DCHECK_GE(window_size, 0);
    DCHECK_LE(window_size, nbytes);
    if (window_size < nbytes) {
      bits_read_ += 8 * window_size;
      return false;
    }
    num_bits -= 8 * nbytes;
    bits_read_ += 8 * nbytes;
  }

  return SkipBitsSmall(num_bits);
}
