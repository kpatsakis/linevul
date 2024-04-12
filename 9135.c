RenderThreadImpl* RenderThreadImpl::Create(
    std::unique_ptr<base::MessageLoop> main_message_loop,
    std::unique_ptr<blink::scheduler::RendererScheduler> renderer_scheduler) {
  return new RenderThreadImpl(std::move(main_message_loop),
                              std::move(renderer_scheduler));
}
