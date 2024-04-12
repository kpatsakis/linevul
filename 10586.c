void WebMediaPlayerImpl::ActivateSurfaceLayerForVideo() {
  DCHECK(!bridge_);

  surface_layer_for_video_enabled_ = true;

  if (video_layer_) {
    client_->SetCcLayer(nullptr);
    video_layer_ = nullptr;
  }

  bridge_ = std::move(create_bridge_callback_)
                .Run(this, compositor_->GetUpdateSubmissionStateCallback());
  bridge_->CreateSurfaceLayer();

  vfc_task_runner_->PostTask(
      FROM_HERE,
      base::BindOnce(
          &VideoFrameCompositor::EnableSubmission,
          base::Unretained(compositor_.get()), bridge_->GetSurfaceId(),
          pipeline_metadata_.video_decoder_config.video_rotation(),
          IsInPictureInPicture(), opaque_,
          BindToCurrentLoop(base::BindRepeating(
              &WebMediaPlayerImpl::OnFrameSinkDestroyed, AsWeakPtr()))));
  bridge_->SetContentsOpaque(opaque_);

  if (client_->DisplayType() ==
      WebMediaPlayer::DisplayType::kPictureInPicture) {
    OnSurfaceIdUpdated(bridge_->GetSurfaceId());
  }
}
