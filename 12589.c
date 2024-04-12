blink::WebSize WebMediaPlayerMS::VisibleRect() const {
  DCHECK(thread_checker_.CalledOnValidThread());
  scoped_refptr<media::VideoFrame> video_frame =
      compositor_->GetCurrentFrameWithoutUpdatingStatistics();
  if (!video_frame)
    return blink::WebSize();

  const gfx::Rect& visible_rect = video_frame->visible_rect();
  if (video_rotation_ == media::VIDEO_ROTATION_90 ||
      video_rotation_ == media::VideoRotation::VIDEO_ROTATION_270) {
    return blink::WebSize(visible_rect.height(), visible_rect.width());
  }
  return blink::WebSize(visible_rect.width(), visible_rect.height());
}
