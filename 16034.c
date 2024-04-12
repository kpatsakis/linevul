void SkiaOutputSurfaceImpl::DiscardBackbuffer() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  auto callback = base::BindOnce(&SkiaOutputSurfaceImplOnGpu::DiscardBackbuffer,
                                 base::Unretained(impl_on_gpu_.get()));
  task_sequence_->ScheduleOrRetainTask(std::move(callback),
                                       std::vector<gpu::SyncToken>());
}
