bool WebRtcAudioRenderer::Initialize(WebRtcAudioRendererSource* source) {
base::AutoLock auto_lock(lock_);
DCHECK_EQ(state_, UNINITIALIZED);
DCHECK(source);
DCHECK(!sink_);
DCHECK(!source_);

sink_ = AudioDeviceFactory::NewOutputDevice();
DCHECK(sink_);

// Ask the browser for the default audio output hardware sample-rate.
// This request is based on a synchronous IPC message.
int sample_rate = GetAudioOutputSampleRate();
DVLOG(1) << "Audio output hardware sample rate: " << sample_rate;
UMA_HISTOGRAM_ENUMERATION("WebRTC.AudioOutputSampleRate",
sample_rate, media::kUnexpectedAudioSampleRate);

// Verify that the reported output hardware sample rate is supported
// on the current platform.
if (std::find(&kValidOutputRates[0],
&kValidOutputRates[0] + arraysize(kValidOutputRates),
sample_rate) ==
&kValidOutputRates[arraysize(kValidOutputRates)]) {
DLOG(ERROR) << sample_rate << " is not a supported output rate.";
return false;
}

media::ChannelLayout channel_layout = media::CHANNEL_LAYOUT_STEREO;

int buffer_size = 0;

// Windows
#if defined(OS_WIN)
// Always use stereo rendering on Windows.
channel_layout = media::CHANNEL_LAYOUT_STEREO;

// Render side: AUDIO_PCM_LOW_LATENCY is based on the Core Audio (WASAPI)
// API which was introduced in Windows Vista. For lower Windows versions,
// a callback-driven Wave implementation is used instead. An output buffer
// size of 10ms works well for WASAPI but 30ms is needed for Wave.

// Use different buffer sizes depending on the current hardware sample rate.
if (sample_rate == 96000 || sample_rate == 48000) {
buffer_size = (sample_rate / 100);
} else {
// We do run at 44.1kHz at the actual audio layer, but ask for frames
// at 44.0kHz to ensure that we can feed them to the webrtc::VoiceEngine.
// TODO(henrika): figure out why we seem to need 20ms here for glitch-
// free audio.
buffer_size = 2 * 440;
}

// Windows XP and lower can't cope with 10 ms output buffer size.
// It must be extended to 30 ms (60 ms will be used internally by WaveOut).
// Note that we can't use media::CoreAudioUtil::IsSupported() here since it
// tries to load the Audioses.dll and it will always fail in the render
// process.
if (base::win::GetVersion() < base::win::VERSION_VISTA) {
buffer_size = 3 * buffer_size;
DLOG(WARNING) << "Extending the output buffer size by a factor of three "
<< "since Windows XP has been detected.";
}
#elif defined(OS_MACOSX)
channel_layout = media::CHANNEL_LAYOUT_MONO;

// Render side: AUDIO_PCM_LOW_LATENCY on Mac OS X is based on a callback-
// driven Core Audio implementation. Tests have shown that 10ms is a suitable
  // frame size to use, both for 48kHz and 44.1kHz.

// Use different buffer sizes depending on the current hardware sample rate.
  if (sample_rate == 48000) {
    buffer_size = 480;
} else {
// We do run at 44.1kHz at the actual audio layer, but ask for frames
// at 44.0kHz to ensure that we can feed them to the webrtc::VoiceEngine.
buffer_size = 440;
}
#elif defined(OS_LINUX) || defined(OS_OPENBSD)
channel_layout = media::CHANNEL_LAYOUT_MONO;

// Based on tests using the current ALSA implementation in Chrome, we have
// found that 10ms buffer size on the output side works fine.
buffer_size = 480;
#else
DLOG(ERROR) << "Unsupported platform";
return false;
#endif

// Store utilized parameters to ensure that we can check them
// after a successful initialization.
params_.Reset(media::AudioParameters::AUDIO_PCM_LOW_LATENCY, channel_layout,
sample_rate, 16, buffer_size);

// Allocate local audio buffers based on the parameters above.
// It is assumed that each audio sample contains 16 bits and each
// audio frame contains one or two audio samples depending on the
// number of channels.
buffer_.reset(new int16[params_.frames_per_buffer() * params_.channels()]);

source_ = source;
source->SetRenderFormat(params_);

// Configure the audio rendering client and start the rendering.
sink_->Initialize(params_, this);
sink_->SetSourceRenderView(source_render_view_id_);
sink_->Start();

state_ = PAUSED;

UMA_HISTOGRAM_ENUMERATION("WebRTC.AudioOutputChannelLayout",
channel_layout, media::CHANNEL_LAYOUT_MAX);
UMA_HISTOGRAM_ENUMERATION("WebRTC.AudioOutputFramesPerBuffer",
buffer_size, kUnexpectedAudioBufferSize);
AddHistogramFramesPerBuffer(buffer_size);

return true;
}
