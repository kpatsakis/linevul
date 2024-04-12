void RenderWidgetHostViewAura::UpdateExternalTexture() {
  if (accelerated_compositing_state_changed_)
    accelerated_compositing_state_changed_ = false;

  bool is_compositing_active = host_->is_accelerated_compositing_active();
  if (is_compositing_active && current_surface_.get()) {
    window_->layer()->SetExternalTexture(current_surface_.get());
    current_frame_size_ = ConvertSizeToDIP(
        current_surface_->device_scale_factor(), current_surface_->size());
    CheckResizeLock();
    software_frame_manager_->DiscardCurrentFrame();
  } else if (is_compositing_active &&
             software_frame_manager_->HasCurrentFrame()) {
    cc::TextureMailbox mailbox;
    scoped_ptr<cc::SingleReleaseCallback> callback;
    software_frame_manager_->GetCurrentFrameMailbox(&mailbox, &callback);
    window_->layer()->SetTextureMailbox(mailbox,
                                        callback.Pass(),
                                        last_swapped_surface_scale_factor_);
    current_frame_size_ = ConvertSizeToDIP(last_swapped_surface_scale_factor_,
                                           mailbox.shared_memory_size());
    CheckResizeLock();
  } else {
    window_->layer()->SetShowPaintedContent();
    resize_lock_.reset();
    host_->WasResized();
    software_frame_manager_->DiscardCurrentFrame();
  }
}
