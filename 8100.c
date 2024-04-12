   int ComputeConsumedBytes(int initial_bytes_enqueued,
                           int initial_bytes_buffered) {
    int byte_delta = bytes_enqueued_ - initial_bytes_enqueued;
    int buffered_delta = algorithm_.bytes_buffered() - initial_bytes_buffered;
    int consumed = byte_delta - buffered_delta;
    CHECK_GE(consumed, 0);
    return consumed;
   }
