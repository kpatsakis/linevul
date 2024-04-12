VaapiVideoDecodeAccelerator::CreateSurface() {
  DCHECK(decoder_thread_task_runner_->BelongsToCurrentThread());
  base::AutoLock auto_lock(lock_);

  if (available_va_surfaces_.empty())
    return nullptr;

  DCHECK(!awaiting_va_surfaces_recycle_);
  scoped_refptr<VASurface> va_surface(new VASurface(
      available_va_surfaces_.front(), requested_pic_size_,
      vaapi_wrapper_->va_surface_format(), va_surface_release_cb_));
  available_va_surfaces_.pop_front();

  return new VaapiDecodeSurface(curr_input_buffer_->id(), va_surface);
}
