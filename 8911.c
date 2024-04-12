void WebMediaPlayerMS::OnRotationChanged(media::VideoRotation video_rotation,
                                         bool is_opaque) {
  DVLOG(1) << __func__;
  DCHECK(thread_checker_.CalledOnValidThread());
  video_rotation_ = video_rotation;
  opaque_ = is_opaque;

  if (!bridge_) {
    auto new_video_layer =
        cc::VideoLayer::Create(compositor_.get(), video_rotation);
    new_video_layer->SetContentsOpaque(is_opaque);

    get_client()->SetCcLayer(new_video_layer.get());

    video_layer_ = std::move(new_video_layer);
  } else {
    compositor_task_runner_->PostTask(
        FROM_HERE, base::BindOnce(&WebMediaPlayerMSCompositor::UpdateRotation,
                                  compositor_, video_rotation));
  }
}
