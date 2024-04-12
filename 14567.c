void Tab::OnPaint(gfx::Canvas* canvas) {
  SkPath clip;
  if (!controller_->ShouldPaintTab(this, canvas->image_scale(), &clip))
    return;

  tab_style()->PaintTab(canvas, clip);
}
