AudioOutputDevice::AudioThreadCallback::AudioThreadCallback(
    const AudioParameters& audio_parameters,
    int input_channels,
    base::SharedMemoryHandle memory,
    int memory_length,
    AudioRendererSink::RenderCallback* render_callback)
    : AudioDeviceThread::Callback(audio_parameters,
                                  input_channels,
                                  memory,
                                  memory_length),
      render_callback_(render_callback) {
}
