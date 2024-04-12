void NsDisable(preproc_effect_t *effect)
{
    ALOGV("NsDisable");
    webrtc::NoiseSuppression *ns = static_cast<webrtc::NoiseSuppression *>(effect->engine);
    ns->Enable(false);
}
