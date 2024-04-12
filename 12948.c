SharedQuadState* CreateSharedQuadState(RenderPass* render_pass) {
  gfx::Transform quad_transform = gfx::Transform(1.0, 0.0, 0.5, 1.0, 0.5, 0.0);
  gfx::Size content_bounds(26, 28);
  gfx::Rect visible_content_rect(10, 12, 14, 16);
  gfx::Rect clip_rect(19, 21, 23, 25);
  bool is_clipped = false;
  float opacity = 1.f;
  int sorting_context_id = 65536;
  SkXfermode::Mode blend_mode = SkXfermode::kSrcOver_Mode;

  SharedQuadState* state = render_pass->CreateAndAppendSharedQuadState();
  state->SetAll(quad_transform,
                content_bounds,
                visible_content_rect,
                clip_rect,
                is_clipped,
                opacity,
                blend_mode,
                sorting_context_id);
  return state;
}
