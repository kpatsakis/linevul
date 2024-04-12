void AecEnable(preproc_effect_t *effect)
{
    webrtc::EchoControlMobile *aec = static_cast<webrtc::EchoControlMobile *>(effect->engine);
    ALOGV("AecEnable aec %p", aec);
    aec->Enable(true);
}
