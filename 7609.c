  RegressionTestData(const char* filename, PipelineStatus init_status,
                     PipelineStatus end_status, const char* video_md5,
                     const char* audio_md5)
      : video_md5(video_md5),
        audio_md5(audio_md5),
        filename(filename),
        init_status(init_status),
        end_status(end_status) {
  }
