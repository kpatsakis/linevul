void MultibufferDataSource::ProgressCallback(int64_t begin, int64_t end) {
  DVLOG(1) << __func__ << "(" << begin << ", " << end << ")";
  DCHECK(render_task_runner_->BelongsToCurrentThread());

  if (assume_fully_buffered())
    return;

  base::AutoLock auto_lock(lock_);

  if (end > begin) {
    if (stop_signal_received_)
      return;

    host_->AddBufferedByteRange(begin, end);
  }

  if (buffer_size_update_counter_ > 0) {
    buffer_size_update_counter_--;
  } else {
    UpdateBufferSizes();
  }
  UpdateLoadingState_Locked(false);
}
