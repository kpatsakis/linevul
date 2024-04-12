int AecInit (preproc_effect_t *effect)
{
    ALOGV("AecInit");
    webrtc::EchoControlMobile *aec = static_cast<webrtc::EchoControlMobile *>(effect->engine);
    aec->set_routing_mode(kAecDefaultMode);
    aec->enable_comfort_noise(kAecDefaultComfortNoise);
 return 0;
}
