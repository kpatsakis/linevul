void RenderFrameHostImpl::OnUpdatePictureInPictureSurfaceId(
    const viz::SurfaceId& surface_id,
    const gfx::Size& natural_size) {
  if (delegate_)
    delegate_->UpdatePictureInPictureSurfaceId(surface_id, natural_size);
}
