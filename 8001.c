void VaapiVideoDecodeAccelerator::Flush() {
  VLOGF(2) << "Got flush request";
  DCHECK(task_runner_->BelongsToCurrentThread());

  QueueInputBuffer(media::BitstreamBuffer());
}
