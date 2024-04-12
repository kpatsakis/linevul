void DelegatedFrameHost::CopyFromCompositingSurface(
    const gfx::Rect& src_subrect,
    const gfx::Size& output_size,
    const ReadbackRequestCallback& callback,
    const SkColorType preferred_color_type) {
  bool format_support = ((preferred_color_type == kAlpha_8_SkColorType) ||
                         (preferred_color_type == kRGB_565_SkColorType) ||
                         (preferred_color_type == kN32_SkColorType));
  DCHECK(format_support);
  if (!CanCopyFromCompositingSurface()) {
    callback.Run(SkBitmap(), content::READBACK_SURFACE_UNAVAILABLE);
    return;
  }

  std::unique_ptr<viz::CopyOutputRequest> request =
      viz::CopyOutputRequest::CreateRequest(
          base::BindOnce(&CopyFromCompositingSurfaceHasResult, output_size,
                         preferred_color_type, callback));
  if (!src_subrect.IsEmpty())
    request->set_area(src_subrect);
  RequestCopyOfOutput(std::move(request));
}
