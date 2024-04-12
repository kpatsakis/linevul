void SoftMPEG2::onReset() {
 SoftVideoDecoderOMXComponent::onReset();

    mWaitForI = true;

    resetDecoder();
    resetPlugin();
}
