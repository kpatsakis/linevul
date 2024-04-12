void RenderFrameHostImpl::GetAudioContextManager(
    blink::mojom::AudioContextManagerRequest request) {
  AudioContextManagerImpl::Create(this, std::move(request));
}
