void SynchronousCompositorImpl::OnComputeScroll(
    base::TimeTicks animation_time) {
  if (need_animate_input_) {
    need_animate_input_ = false;
    synchronous_input_handler_proxy_->SynchronouslyAnimate(animation_time);
  }
}
