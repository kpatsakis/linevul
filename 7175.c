NPError WebPluginDelegatePepper::Device3DInitializeContext(
    const NPDeviceContext3DConfig* config,
    NPDeviceContext3D* context) {
#if defined(ENABLE_GPU)
  if (nested_delegate_)
    return NPERR_GENERIC_ERROR;

  nested_delegate_ = new WebPluginDelegateProxy(kGPUPluginMimeType,
                                                render_view_);

  if (nested_delegate_->Initialize(GURL(),
                                   std::vector<std::string>(),
                                   std::vector<std::string>(),
                                   plugin_,
                                   false)) {
    plugin_->SetAcceptsInputEvents(true);

    command_buffer_.reset(nested_delegate_->CreateCommandBuffer());
    if (command_buffer_.get()) {
      if (command_buffer_->Initialize(config->commandBufferEntries)) {
        gpu::CommandBuffer::State state = command_buffer_->GetState();

        context->reserved = NULL;
        Buffer ring_buffer = command_buffer_->GetRingBuffer();
        context->commandBuffer = ring_buffer.ptr;
        context->commandBufferEntries = state.size;
        Synchronize3DContext(context, state);

        nested_delegate_->UpdateGeometry(window_rect_, clip_rect_);
        Device3DImpl* impl = new Device3DImpl;
        impl->command_buffer = command_buffer_.get();
        context->reserved = impl;

        return NPERR_NO_ERROR;
      }
    }

    command_buffer_.reset();
  }

  nested_delegate_->PluginDestroyed();
  nested_delegate_ = NULL;
#endif  // ENABLE_GPU

  return NPERR_GENERIC_ERROR;
}
