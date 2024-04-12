void OmniboxViewViews::OnPaint(gfx::Canvas* canvas) {
  if (latency_histogram_state_ == CHAR_TYPED) {
    DCHECK(!insert_char_time_.is_null());
    UMA_HISTOGRAM_TIMES("Omnibox.CharTypedToRepaintLatency.ToPaint",
                        base::TimeTicks::Now() - insert_char_time_);
    latency_histogram_state_ = ON_PAINT_CALLED;
  }

  {
    SCOPED_UMA_HISTOGRAM_TIMER("Omnibox.PaintTime");
    Textfield::OnPaint(canvas);
  }
}
