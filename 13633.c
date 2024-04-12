void VaapiVideoDecodeAccelerator::FinishReset() {
  DCHECK_EQ(message_loop_, base::MessageLoop::current());
  DVLOG(1) << "FinishReset";
  base::AutoLock auto_lock(lock_);

  if (state_ != kResetting) {
    DCHECK(state_ == kDestroying || state_ == kUninitialized) << state_;
    return;  // We could've gotten destroyed already.
  }

  while (!pending_output_cbs_.empty())
    pending_output_cbs_.pop();

  if (awaiting_va_surfaces_recycle_) {
    message_loop_->PostTask(FROM_HERE, base::Bind(
        &VaapiVideoDecodeAccelerator::FinishReset, weak_this_));
    return;
  }

  num_stream_bufs_at_decoder_ = 0;
  state_ = kIdle;

  message_loop_->PostTask(FROM_HERE, base::Bind(
      &Client::NotifyResetDone, client_));

  if (!input_buffers_.empty()) {
    state_ = kDecoding;
    decoder_thread_task_runner_->PostTask(
        FROM_HERE, base::Bind(&VaapiVideoDecodeAccelerator::DecodeTask,
                              base::Unretained(this)));
  }

  DVLOG(1) << "Reset finished";
}
