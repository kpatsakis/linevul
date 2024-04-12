  void CreateUnifiedStream(const url::Origin& security_origin) {
    std::string output_id = GetNondefaultIdExpectedToPassPermissionsCheck();
    std::string input_id = GetNondefaultInputId();
    std::string hashed_output_id = MediaStreamManager::GetHMACForMediaDeviceID(
        kSalt, url::Origin(GURL(kSecurityOrigin)), output_id);
    audio_manager_->CreateDeviceAssociation(input_id, output_id);
    int session_id = media_stream_manager_->audio_input_device_manager()->Open(
        StreamDeviceInfo(MEDIA_DEVICE_AUDIO_CAPTURE, "Fake input device",
                         input_id));
    base::RunLoop().RunUntilIdle();

    media::AudioParameters params(
        media::AudioParameters::AUDIO_FAKE, media::CHANNEL_LAYOUT_STEREO,
        media::AudioParameters::kAudioCDSampleRate, 16,
        media::AudioParameters::kAudioCDSampleRate / 10);

    EXPECT_CALL(*host_.get(),
                OnDeviceAuthorized(kStreamId, media::OUTPUT_DEVICE_STATUS_OK, _,
                                   hashed_output_id))
        .Times(1);
    EXPECT_CALL(*host_.get(), WasNotifiedOfCreation(kStreamId, _));
    EXPECT_CALL(mirroring_manager_, AddDiverter(render_process_host_.GetID(),
                                                kRenderFrameId, NotNull()))
        .RetiresOnSaturation();
    EXPECT_CALL(mirroring_manager_, RemoveDiverter(NotNull()))
        .RetiresOnSaturation();

    host_->OnRequestDeviceAuthorization(kStreamId, kRenderFrameId, session_id,
                                        /*device id*/ std::string(),
                                        security_origin);

    auth_run_loop_.Run();

    host_->OnCreateStream(kStreamId, kRenderFrameId, params);

    SyncWithAudioThread();
  }
