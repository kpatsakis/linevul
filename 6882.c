void WebGLRenderingContextBase::DrawingBufferClientRestoreMaskAndClearValues() {
  if (!ContextGL())
    return;
  bool color_mask_alpha =
      color_mask_[3] && active_scoped_rgb_emulation_color_masks_ == 0;
  ContextGL()->ColorMask(color_mask_[0], color_mask_[1], color_mask_[2],
                         color_mask_alpha);
  ContextGL()->DepthMask(depth_mask_);
  ContextGL()->StencilMaskSeparate(GL_FRONT, stencil_mask_);

  ContextGL()->ClearColor(clear_color_[0], clear_color_[1], clear_color_[2],
                          clear_color_[3]);
  ContextGL()->ClearDepthf(clear_depth_);
   ContextGL()->ClearStencil(clear_stencil_);
 }
