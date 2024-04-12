blink::WebSize WebMediaPlayerImpl::VisibleRect() const {
  DCHECK(main_task_runner_->BelongsToCurrentThread());
  scoped_refptr<VideoFrame> video_frame = GetCurrentFrameFromCompositor();
  if (!video_frame)
    return blink::WebSize();

  const gfx::Rect& visible_rect = video_frame->visible_rect();
  return blink::WebSize(visible_rect.width(), visible_rect.height());
}
