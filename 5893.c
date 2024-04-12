SkiaOutputSurfaceImpl::~SkiaOutputSurfaceImpl() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  current_paint_.reset();
  root_recorder_.reset();

  std::vector<std::unique_ptr<ImageContextImpl>> render_pass_image_contexts;
  render_pass_image_contexts.reserve(render_pass_image_cache_.size());
  for (auto& id_and_image_context : render_pass_image_cache_) {
    id_and_image_context.second->clear_image();
    render_pass_image_contexts.push_back(
        std::move(id_and_image_context.second));
  }

  base::WaitableEvent event;
  auto callback = base::BindOnce(
      [](std::vector<std::unique_ptr<ImageContextImpl>> render_passes,
         std::unique_ptr<SkiaOutputSurfaceImplOnGpu> impl_on_gpu,
         base::WaitableEvent* event) {
        if (!render_passes.empty())
          impl_on_gpu->RemoveRenderPassResource(std::move(render_passes));
        impl_on_gpu = nullptr;
        event->Signal();
      },
      std::move(render_pass_image_contexts), std::move(impl_on_gpu_), &event);
  ScheduleGpuTask(std::move(callback), std::vector<gpu::SyncToken>());
  event.Wait();

  task_sequence_ = nullptr;
}
