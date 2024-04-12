void VaapiVideoDecodeAccelerator::ReturnCurrInputBuffer_Locked() {
  DCHECK(decoder_thread_task_runner_->BelongsToCurrentThread());
  lock_.AssertAcquired();
  DCHECK(curr_input_buffer_.get());
  curr_input_buffer_.reset();

  TRACE_COUNTER1("Video Decoder", "Input buffers", input_buffers_.size());
}
