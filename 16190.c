void VaapiVideoDecodeAccelerator::ResetTask() {
  DCHECK(decoder_thread_task_runner_->BelongsToCurrentThread());
  DVLOG(1) << "ResetTask";

  decoder_->Reset();

  base::AutoLock auto_lock(lock_);

  if (curr_input_buffer_.get())
    ReturnCurrInputBuffer_Locked();

  message_loop_->PostTask(FROM_HERE, base::Bind(
      &VaapiVideoDecodeAccelerator::FinishReset, weak_this_));
}
