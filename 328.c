  media::AudioRenderer::AudioTimeCB NewAudioTimeClosure() {
    return base::Bind(&AudioRendererImplTest::OnAudioTimeCallback,
                      base::Unretained(this));
  }
