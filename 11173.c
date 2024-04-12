static BrotliResult BROTLI_NOINLINE CopyUncompressedBlockToOutput(
    size_t* available_out, uint8_t** next_out, size_t* total_out,
    BrotliState* s) {
  /* State machine */
  for (;;) {
    switch (s->substate_uncompressed) {
      case BROTLI_STATE_UNCOMPRESSED_NONE: {
        int nbytes = (int)BrotliGetRemainingBytes(&s->br);
        if (nbytes > s->meta_block_remaining_len) {
          nbytes = s->meta_block_remaining_len;
        }
        if (s->pos + nbytes > s->ringbuffer_size) {
          nbytes = s->ringbuffer_size - s->pos;
        }
        /* Copy remaining bytes from s->br.buf_ to ringbuffer. */
        BrotliCopyBytes(&s->ringbuffer[s->pos], &s->br, (size_t)nbytes);
        s->pos += nbytes;
        s->meta_block_remaining_len -= nbytes;
        if (s->pos < s->ringbuffer_size) {
          if (s->meta_block_remaining_len == 0) {
            return BROTLI_RESULT_SUCCESS;
          }
          return BROTLI_RESULT_NEEDS_MORE_INPUT;
        }
        s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_WRITE;
        /*s->partial_pos_rb += (size_t)s->ringbuffer_size;*/
        /* No break, continue to next state */
      }
      case BROTLI_STATE_UNCOMPRESSED_WRITE: {
        BrotliResult result = WriteRingBuffer(
            available_out, next_out, total_out, s);
        if (result != BROTLI_RESULT_SUCCESS) {
          return result;
        }
        s->pos = 0;
        s->rb_roundtrips++;
        s->max_distance = s->max_backward_distance;
        s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_NONE;
        break;
      }
    }
  }
  return BROTLI_FAILURE();
}
