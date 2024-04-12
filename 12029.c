void VaapiVideoDecodeAccelerator::InitiateSurfaceSetChange(size_t num_pics,
                                                           gfx::Size size) {
  DCHECK_EQ(message_loop_, base::MessageLoop::current());
  DCHECK(!awaiting_va_surfaces_recycle_);

  DVLOG(1) << "Initiating surface set change";
  awaiting_va_surfaces_recycle_ = true;

  requested_num_pics_ = num_pics;
  requested_pic_size_ = size;

  TryFinishSurfaceSetChange();
}
